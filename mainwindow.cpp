#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FocusStack.h"
#include "opencvtoqt.h"
#include "globals.h"
#include "settingsdialog.h"
#include "findtargets.h"
#include "imageprocessing.h"
#include "HelperFunctions.h"
#include "imagesContainer.h"
#include "targeterimage.h"

#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QSettings>
#include <QListWidgetItem>
#include <QBitmap>
#include <cmath>
#include <QStandardPaths>
#include <QXmlStreamWriter>

#include "opencv2/core.hpp"
#include "opencv/highgui.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video.hpp"

#ifdef PYLON
#include <pylon/PylonIncludes.h>
using namespace Pylon;
#endif

using namespace cv;
using namespace std;



/*
    QIcon targeterIcon;
    try
    {
      targeterIcon.addFile(":icons/24/targeter.png", QSize(24, 24));
      QIcon deleteIcon = QIcon::fromTheme("edit-delete");

      ui->actionProcessFocusStack->setIcon(targeterIcon);
      ui->actionDelete_Selected_Images->setIcon(deleteIcon);

    }
    catch( cv::Exception& e )
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
*/

/**
*
*  class constructor: sets up slots, initializes variables, gets serialised settings values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::MainWindow
* Qualifier  : QMainWindow(parent), ui(new Ui::MainWindow)
* @param     QWidget * parent 
* @return    
* Access     public 
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    //m_CurrentQImage = NULL;
    this->m_scale = 1;

#ifdef PYLON
    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();
#endif

    ui->setupUi(this);

    ui->action_Open->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->action_Save->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));

    ui->ImageThumbList->setStyleSheet("QVectorWidget { background-color: "+QApplication::palette().color(QPalette::Window).name()+";}");
    //{background-color:red; border: 1px solid red }

    QPalette palette = ui->ImageThumbList->palette();

    palette.setColor(ui->ImageThumbList->backgroundRole(), ui->display_image->palette().color(QWidget::backgroundRole()));
    palette.setColor(ui->ImageThumbList->foregroundRole(), ui->display_image->palette().color(QWidget::backgroundRole()));

    ui->ImageThumbList->setAutoFillBackground(true);
    ui->ImageThumbList->setPalette(palette);

    // handle thumbnail click
    QObject::connect(ui->ImageThumbList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onThumbImageClick(QListWidgetItem*)));

    // handle checkbox click
    QObject::connect(ui->ImageThumbList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onImageChecked(QListWidgetItem*)));

    // slots for communication from printqlabel class
    QObject::connect(ui->display_image, SIGNAL(disablePanButton()), this, SLOT(disablePanButton()));
    QObject::connect(ui->display_image, SIGNAL(setTargetArea(drawingShape)), this, SLOT(setTargetArea(drawingShape)));
    QObject::connect(ui->display_image, SIGNAL(unsetDrawingButtons()), this, SLOT(unsetDrawingButtons()));

	ui->ImageThumbList->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui->ImageThumbList, SIGNAL(customContextMenuRequested(const QPoint &)),
		this, SLOT(ProvideContextMenu(const QPoint &)));

	// set up context menu
	m_thumb_context_menu.toolTipsVisible();

	m_thumb_context_menu.addAction(ui->actionSet_as_Target);
	m_thumb_context_menu.addAction(ui->actionSet_as_find_targets_image);
	m_thumb_context_menu.addAction(ui->actionDeleteImage);

	fh_addFileListToMenu();

	m_bContextMenuAction = false;

	QFile file("targetter_settings.dat");
	
	if (file.open(QIODevice::ReadOnly)) {
		QDataStream in(&file);   // we will serialize the data into the file
		m_settings.deserialize(in);
	}
	else
	{
		m_settings.algorithmType = algoType::COOC;
		m_settings.cluster = 50;
		m_settings.distance = 50;
		m_settings.threshold_min = 0;
		m_settings.threshold_max = 255;
		m_settings.autoThreshold = true;
		m_settings.ScoreThreshold = 70;
		m_settings.NoClustersThreshold = 2;
	}

	file.close();
}

// 

/**
*
* makes context menu for image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::ProvideContextMenu
* Qualifier 
* @param     const QPoint & pos 
* @return    void
* Access     private 
*/
void MainWindow::ProvideContextMenu(const QPoint &pos)
{
	QPoint item = ui->ImageThumbList->mapToGlobal(pos);

	//QWidget *widget = static_cast<QListWidgetItem*>(childAt(pos));

	m_bContextMenuAction = true;

	QAction* rightClickItem = m_thumb_context_menu.exec(item);

	m_bContextMenuAction = false;
}


/**
*
*  Manages recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_addFileListToMenu
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::fh_addFileListToMenu()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    // create actions for recent files
    for (int i = 0; i < MaxRecentFiles; ++i) {
           recentFileActs[i] = new QAction(this);
           recentFileActs[i]->setVisible(false);
           connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    separatorAct = menus[0]->addSeparator();

    //add action to menu bar
    for (int i = 0; i < MaxRecentFiles; ++i)
		menus[0]->addAction(recentFileActs[i]);

    menus[0]->addSeparator();

    fh_updateRecentFileActions();
}


/**
*
*  Sets current file for recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_setCurrentFile
* Qualifier 
* @param     const QString & fileName 
* @return    void
* Access     public 
*/
void MainWindow::fh_setCurrentFile(const QString &fileName)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    fh_updateRecentFileActions();
}


/**
*
*  Update actions for recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_updateRecentFileActions
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::fh_updateRecentFileActions()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(fh_strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

/**
*
*  gets just file name from full filenamepath
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_strippedName
* Qualifier 
* @param     const QString & fullFileName 
* @return    QT_NAMESPACE::QString
* Access     public 
*/
QString MainWindow::fh_strippedName(const QString &fullFileName)
{   
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
}

/*
void MainWindow::wheelEvent ( QWheelEvent * event )
{
    this->m_scale += (event->delta()/120); //or use any other step for zooming
    std::cout << "exception caught: " << this->m_scale << std::endl;


}
*/

/**
*
*  Saves current image to file
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::SaveImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::SaveImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName(this, "Save Image File","",tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.gif, *.tif, *.tiff]"));

    if(fileName != "" )
    {
		int ind = getValidImageIndex();

		QImage& image = m_ImagesContainer.getImageAt(ind).getQTImage();

		image.save(fileName.toLocal8Bit().data());
        //cv::imwrite(fileName.toLocal8Bit().data(), *m_pCurrentImage );
    }
}

/**
*
*  Opens recent file from list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::openRecentFile
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::openRecentFile()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

/**
*
* loads image file  
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::loadFile
* Qualifier 
* @param     const QString & fileName 
* @return    void
* Access     public 
*/
void MainWindow::loadFile(const QString &fileName)
{

#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	 addImage(fileName, imageType::display);

	 int i = m_ImagesContainer.getNumImages();

     if(i>0)
     {
		 try
		 {
			 m_currentImageDisplayedIndex = i - 1;

             DisplayImage();
         }
         catch( cv::Exception& e )
         {
             const char* err_msg = e.what();
             std::cout << "exception caught: " << err_msg << std::endl;
         }
     }
}

/**
*
*  Displays message box depending on image type
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::showMessage
* Qualifier 
* @param     imageType::imageType type 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::showMessage(imageType::imageType type, QMessageBox::Icon icn)
{
	QString msg("A image of type");

	if (type == imageType::mask)
		msg += " mask ";
	else if (type == imageType::target)
		msg += " target ";
	else if (type == imageType::test)
		msg += " test ";
	else if (type == imageType::roi)
		msg += " region of interest ";
	else if (type == imageType::cclabels)
		msg += " connected components ";
	else
		msg += " different to this one ";

	msg += "is required for this function";

	showMessage(msg);
}

/**
*
*  Displays message box
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::showMessage
* Qualifier 
* @param     QString message 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::showMessage(QString message, QMessageBox::Icon icn)
{
	QMessageBox mb;
	QPixmap p(":icons/24/targeter.png");
	mb.setIcon(icn);
	mb.setWindowIcon(p);
	mb.setWindowTitle(QString("Targeter Message"));
	mb.setText(QString(message));
	mb.exec();
}

/**
*
*  Sets image histogram in settings dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::setHistogramImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::setHistogramImage()
{
	// get histogram image
	cv::Mat hIm = getHistogram();

	if (hIm.rows > 0)
	{
		// convert to qt image
		QImage qim = HelperFunctions::makeQImage(hIm);

		m_settingsDlg.setHistogramImage(qim);
	}
}

/**
*
* Gets image histogram 
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::getHistogram
* Qualifier 
* @return    cv::Mat
* Access     public 
*/
cv::Mat MainWindow::getHistogram()
{
	int histSize = 255;

	float range[] = { 0, histSize };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	cv::Mat hIm;

	if (m_ImagesContainer.getNumImages() > 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(m_currentImageDisplayedIndex).getImage();

		if (!im.empty())
		{
			cv::Mat b_hist;

			cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);

			calcHist(&im, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

			// get histogram image
			hIm = HelperFunctions::displayHistogram(histSize, b_hist);
		}
	}
	return hIm;
}


/**
*
*  Creates targeter image and QImage for display from OpenCV image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addCVImage
* Qualifier 
* @param     cv::Mat im 
* @param     QString imageName 
* @param     bool bRGBSwap 
* @param     imageType type 
* @return    void
* Access     public 
*/
void MainWindow::addCVImage(cv::Mat im, QString imageName, bool bRGBSwap, imageType::imageType type, bool bDisplay)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	targeterImage tim(&m_ImagesContainer);

	tim.addImageEx(im, type, imageName.toLocal8Bit().data());

	addCVImage(tim, imageName, bRGBSwap);
}


/**
*
*  Creates QImage for display from targeter image and displays image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addCVImage
* Qualifier 
* @param     targeterImage & tim 
* @param     QString imageName 
* @param     bool bRGBSwap 
* @return    void
* Access     public 
*/
void MainWindow::addCVImage(targeterImage& tim, QString imageName, bool bRGBSwap)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	addQImageThumbnail(tim.getQTImage(), imageName, tim.getImageFunction());

	m_ImagesContainer.addImage(tim);

	m_currentImageDisplayedIndex = m_ImagesContainer.getNumImages() - 1;

	DisplayImage();
}

/**
*
*  Given a file name loads and reads image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addImage
* Qualifier 
* @param     const QString & fileName 
* @param     imageType type 
* @return    void
* Access     public 
*/
void MainWindow::addImage(const QString &fileName, imageType::imageType type)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    QString qs = fileName;
    String s = qs.toLocal8Bit().data();

	fh_setCurrentFile(qs);

	targeterImage tim(&m_ImagesContainer);

    cv::Mat im = imread(s);

	addCVImage(im, qs, true, imageType::display, false);
}

/**
*
*  Makes sub image from rectangular region of image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::copyImageToSquareRegion
* Qualifier 
* @param     QImage qim 
* @param     QColor col 
* @return    QT_NAMESPACE::QImage
* Access     public 
*/
QImage MainWindow::copyImageToSquareRegion(QImage qim, QColor col)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QPoint pt;
    QImage destImage;

    if(qim.width()> qim.height())
    {
        destImage = QImage(qim.width(), qim.width(), qim.format());

        destImage.fill(col);

        pt = QPoint(0, (qim.width()-qim.height())>>1);
    }
    else
    {
        destImage = QImage(qim.height(), qim.height(), qim.format());

        destImage.fill(col);

        pt = QPoint((qim.height()-qim.width())>>1, 0);
    }

    QPainter painter(&destImage);

    painter.drawImage(pt, qim);
    painter.end();

    return destImage;
}

/**
*
*  update labels of thumbnail images
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::updateThumbs
* Qualifier 
* @param     int index 
* @return    void
* Access     public 
*/
void MainWindow::updateThumbs(int index)
{
	QString s = "";

	for (int row = 0; row < ui->ImageThumbList->count(); row++)
	{
		targeterImage& t = m_ImagesContainer.getImageAt(row);

		imageType::imageType type = t.getImageFunction();

		s = QString::fromStdString(t.getName());

		if (type == imageType::target)
			s = "target image";
		else if (type == imageType::test)
			s = "detection image";

		ui->ImageThumbList->item(row)->setText(s.section("/", -1));
	}
}

/**
*
*  adds QImage to thumbnail list
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::addQImage
* Qualifier
* @param     QImage & qim
* @param     QString imageName
* @param     imageType type
* @return    void
* Access     public
*/
void MainWindow::addQImageThumbnail(QImage& qim, QString imageName, imageType::imageType type)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QImage iconImage = copyImageToSquareRegion(qim, ui->display_image->palette().color(QWidget::backgroundRole()));

	QListWidgetItem* pItem = new QListWidgetItem(QIcon(QPixmap::fromImage(iconImage)), NULL);//QFileInfo(qs).fileName());

	pItem->setData(Qt::UserRole, "thumb" + QString::number(ui->ImageThumbList->count()));
	pItem->setToolTip(imageName);

	if (type == imageType::target)
		pItem->setText("target image");
	else if (type == imageType::test)
		pItem->setText("detection image");

	pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
	pItem->setCheckState(Qt::Unchecked);

	ui->ImageThumbList->addItem(pItem);
}

/*
 * // code in function below
String s = qs.toLocal8Bit().data();

m_filenames.push_back(s);

Mat im = imread(s);

setCurrentFile(qs);

m_ImagesContainer.m_Images.push_back(im);

QImage::Format form = this->getFormat(im.type());

QImage qi = QImage(im.data, im.cols, im.rows, im.step, form);

QImage qim = qi.rgbSwapped();

m_QImages.push_back(qim);

QlistWidgetItem* pItem = new QlistWidgetItem(QIcon(QPixmap::fromImage(qim)), NULL);//QFileInfo(qs).fileName());

pItem->setToolTip(qs);

pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
pItem->setCheckState(Qt::Unchecked);

ui->ImageThumbList->addItem(pItem);
*/

/**
*
*  Handles Opening of image from file open dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::OpenImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::OpenImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);


    QStringList fileNames;

	try 
	{
		QStringList s=QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

		QString st = s[0];

		if (m_ImagesContainer.getNumImages() > 0)
			st = "";

		// unfortunately cannot use native file dialog as it crashes on network drive access
		fileNames = dialog.getOpenFileNames(this, tr("Open Image"), st, tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.gif, *.tif, *.tiff]"), 0, QFileDialog::DontUseNativeDialog);
	}
	catch (...) {
		DBOUT("error opening file");
	}

    QMutableStringListIterator i(fileNames); // pass list as argument

    while (i.hasNext()) {
        QString qs = i.next();

        addImage(qs);
    }

	int num = m_ImagesContainer.getNumImages();

    if(num>0)
    {
        try
        {
			m_currentImageDisplayedIndex = num - 1;
			
            DisplayImage();
        }
        catch( cv::Exception& e )
        {
            const char* err_msg = e.what();
            std::cout << "exception caught: " << err_msg << std::endl;
        }
    }
}

/**
*
*  Highlights image thumbnail list items
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::onImageChecked
* Qualifier 
* @param     QListWidgetItem * item 
* @return    void
* Access     private 
*/
void MainWindow::onImageChecked(QListWidgetItem* item)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    if(item->checkState() == Qt::Checked)
    {
		QColor c("#b9fcb6");
		QBrush brush(c, Qt::SolidPattern);
      
		//QString s = "QListWidget::item[UserRole=" + item->data(Qt::UserRole).toString() + "]  { border: 1px solid red }";
	
		//item->listWidget()->setStyleSheet(s);
		
		item->setBackground(brush);
    }
    else
    {
       QBrush brush(Qt::NoBrush);

       item->setBackground(brush);
    }
}

/**
*
*  Changes displayed image when thumbnail image clicked
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::onThumbImageClick
* Qualifier 
* @param     QListWidgetItem * item 
* @return    void
* Access     private 
*/
void MainWindow::onThumbImageClick(QListWidgetItem* item)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	// Set the main image to be the clicked thumbnail image.
	int ind = ui->ImageThumbList->currentRow();

	if (ind < (int)m_ImagesContainer.getNumImages() && ind >= 0)
	{
		m_currentImageDisplayedIndex = ind;

		try
		{
			m_currentImageDisplayedIndex = ind;

			DisplayImage();
		}
		catch (cv::Exception& e)
		{
			const char* err_msg = e.what();
			std::cout << "exception caught: " << err_msg << std::endl;
		}
	}
}


/**
*
*  Get vector of checked images in list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::getCheckedImages
* Qualifier 
* @return    QVector<int>
* Access     public 
*/
std::vector<int> MainWindow::getCheckedImages()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	std::vector<int> checkedItems;

    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        if (ui->ImageThumbList->item(row)->checkState() == Qt::Checked)
        {
            checkedItems.push_back(row);
        }
    }
    return checkedItems;
}


/**
*
*  class destructor, serializes settings values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::~MainWindow
* Qualifier 
* @return    
* Access     public 
*/
MainWindow::~MainWindow()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QFile file("targetter_settings.dat");

	if (file.open(QIODevice::WriteOnly))
	{
		QDataStream out(&file);   // we will serialize the data into the file

		m_settings.serialize(out);

		file.close();
	}
    delete ui;

	m_ImagesContainer.freeImages();

   
#ifdef PYLON
    PylonTerminate();
#endif
}

/**
*
*  manage image redrawing when window resized
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::resizeEvent
* Qualifier 
* @param     QResizeEvent * event 
* @return    void
* Access     public 
*/
void MainWindow::resizeEvent(QResizeEvent* event)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

   QMainWindow::resizeEvent(event);
   // Your code here.

    this->DisplayImage();
}


/**
*
*  Gets valid image array index, if current image index is invalid then function returns last valid index
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::getValidImageIndex
* Qualifier 
* @return    int
* Access     public 
*/
int MainWindow::getValidImageIndex()
{
	if (m_currentImageDisplayedIndex >= 0 && m_ImagesContainer.getNumImages() > 0)
	{
		if (m_currentImageDisplayedIndex <m_ImagesContainer.getNumImages() && !m_ImagesContainer.getImageAt(m_currentImageDisplayedIndex).getQTImage().isNull())
		{
			return m_currentImageDisplayedIndex;
		}
		else    // handle case of invalid index, set to last image in list
		{
			for (int i =m_ImagesContainer.getNumImages() - 1; i >= 0; i--)
			{
				if (!m_ImagesContainer.getImageAt(i).getQTImage().isNull())
				{
					m_currentImageDisplayedIndex = i;
					return m_currentImageDisplayedIndex;
				}
			}
			
			m_currentImageDisplayedIndex = -1;
			return m_currentImageDisplayedIndex;
		}
	}
	return -1;
}

/**
*
*  Displays image in widget
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::DisplayImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::DisplayImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		ui->display_image->setImage(m_ImagesContainer.getImageAt(ind).getQTImage());
		ui->display_image->getDisplayRect();
		updateThumbs(ind);
	}
}

/**
*
*  slot for Open file dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Open_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Open_triggered()
{
    OpenImage();
}



/**
*
*  slot for performing focus stack
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionProcessFocusStack_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionProcessFocusStack_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	showMessage("Focus stack function under development");
	return;

    if(ui->ImageThumbList->count()>0)
    {
		std::vector<int> check = getCheckedImages();

		// get all checked images

        cv::Mat* pMat = FocusStack::processImageStack(m_ImagesContainer.getImages(), check, this);

		addCVImage(*pMat, "focus image");
    }
}

/**
*
*  Slot to save image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Save_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Save_triggered()
{
    SaveImage();
}

/**
*
*  slot to select (check) all image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSelect_All_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSelect_All_triggered()
{
    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        ui->ImageThumbList->item(row)->setCheckState(Qt::Checked);
    }
}

/**
*
*  slot to deselect (uncheck) all image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeselect_All_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeselect_All_triggered()
{
    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        ui->ImageThumbList->item(row)->setCheckState(Qt::Unchecked);
    }
}

/**
*
*  Makes new image from ROI rect
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::setTargetArea
* Qualifier 
* @param     drawingShape shape 
* @return    void
* Access     private 
*/
void MainWindow::setTargetArea(drawingShape shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    qDebug() <<m_ImagesContainer.getNumImages() << endl;

	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		createMaskImage(m_ImagesContainer.getImageAt(ind).getImage(), shape);
	}
}

/**
*
*  Gets binary mask image and sub image from region from drawing object shape
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::maskImage
* Qualifier 
* @param     Mat im 
* @param     drawingShape shape 
* @param     targeterImage & tim 
* @return    void
* Access     public 
*/
void MainWindow::createMaskImage(Mat im, drawingShape shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    int x = max(0, min(shape.boundingBox.left(), im.cols));
    int y = max(0, min(shape.boundingBox.top(), im.rows));
    int w = max(0, min(shape.boundingBox.width(), im.cols));
    int h = max(0, min(shape.boundingBox.height(), im.rows));

    cv::Rect roi(x, y, w, h);
	cv::Mat mask, dst = im(roi);

    cv::Mat out = cv::Mat(roi.height, roi.width, im.type(), Scalar(0,0,0));

    // get mask image
    if(shape.type == drawingMode::poly)
    {
        // convert polygon to opencv polygon
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(0, 0, 0));

        vector <cv::Point> triOut;

        // since poly must be in mask image
        foreach(QPoint p, shape.polygon)    
            triOut.push_back(cv::Point(p.x()-shape.boundingBox.left(), p.y()-shape.boundingBox.top()));

        cv::fillConvexPoly(mask, triOut, Scalar( 255, 255, 255));
    }
    else if(shape.type == drawingMode::circle)
    {
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(0, 0, 0));
        cv::ellipse(mask, cv::Point(mask.cols>>1, mask.rows>>1), cv::Size(mask.cols>>1, mask.rows>>1), 0, 0, 360, Scalar( 255, 255, 255 ), -1);
    }
    else
    {
        //return dst;   // dst is with correct colour
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(255, 255, 255));
    }

    //dst.copyTo(out, mask);

	targeterImage tim(&m_ImagesContainer);

	tim.setImageType(imageType::target);

	tim.addImage(dst);

	if (shape.type == drawingMode::circle || shape.type == drawingMode::poly)
	{
		int* pImage = new int[w*h];

		for(int i=0;i<w;i++)
			for (int j = 0; j < h; j++)
				pImage[i + j*w] = (int)(mask.at<Vec3b>(j, i)[0]>0?1:0);

		tim.set1DImage(pImage, imageType::mask);
	}

	addCVImage(tim, "target image", true);

	targeterImage m(&m_ImagesContainer);

	m.setImageType(imageType::mask);

	m.addImage(mask);
	m.setName("target mask image");

	addCVImage(m, "target mask image", true);
}

/**
*
*  slot to stop panning image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::disablePanButton
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::disablePanButton()
{
    ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot for handling zoom out
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionZoom_Out_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionZoom_Out_triggered()
{
    ui->display_image->zoomToPoint(QPoint(ui->display_image->m_displayRect.width()>>1, ui->display_image->m_displayRect.height()>>1), 50);
    ui->display_image->repaint();
}

/**
*
*  slot for handling zoom in
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionZoom_In_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionZoom_In_triggered()
{
    ui->display_image->zoomToPoint(QPoint(ui->display_image->m_displayRect.width()>>1, ui->display_image->m_displayRect.height()>>1), -50);
    ui->display_image->repaint();
}

/**
*
*  slot for handling drawing polygon
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Polygon_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Polygon_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Polygon->isChecked())
        ui->display_image->setDrawingMode(drawingMode::poly);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
    ui->actionDraw_Rectangular_Region->setChecked(false);
    ui->actionDraw_Circle_Region->setChecked(false);
    //ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot for handling drawing circle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Circle_Region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Circle_Region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Circle_Region->isChecked())
        ui->display_image->setDrawingMode(drawingMode::circle);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
    ui->actionDraw_Polygon->setChecked(false);
    ui->actionDraw_Rectangular_Region->setChecked(false);
    //ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot for handling drawing rectangle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Rectangular_Region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Rectangular_Region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Rectangular_Region->isChecked())
        ui->display_image->setDrawingMode(drawingMode::rect);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
    ui->actionDraw_Polygon->setChecked(false);
    ui->actionDraw_Circle_Region->setChecked(false);
    //ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot for handling panning image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Move_Image_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Move_Image_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
   ui->display_image->setPanMode(ui->action_Move_Image->isChecked());
   //ui->actionDraw_Polygon->setChecked(false);
   //ui->actionDraw_Circle_Region->setChecked(false);
   //ui->actionDraw_Rectangular_Region->setChecked(false);
}

/**
*
*  slot for deselecting all drawing buttons
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::unsetDrawingButtons
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::unsetDrawingButtons()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    ui->actionDraw_Polygon->setChecked(false);
    ui->actionDraw_Circle_Region->setChecked(false);
    ui->actionDraw_Rectangular_Region->setChecked(false);
    ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot to get target image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionGet_Target_image_region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionGet_Target_image_region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int ind = getValidImageIndex();

	if (ind >= 0)
        ui->display_image->getTargetImage();
}

/**
*
*  sets type of image
*
* @author    David Watts
* @since     2017/03/14
* 
* FullName   MainWindow::updateImageType
* Qualifier 
* @param     int ind 
* @param     imageType::imageType type 
* @return    void
* Access     public 
*/
void MainWindow::updateImageType(int ind, imageType::imageType type)
{
	if (m_ImagesContainer.getImageAt(ind).getImageFunction() == type)
		m_ImagesContainer.getImageAt(ind).setImageType(imageType::display);
	else
		m_ImagesContainer.getImageAt(ind).setImageType(type);
}


/**
*
*  slot to flag image as target image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSet_as_find_targets_image_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSet_as_find_targets_image_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (m_bContextMenuAction)
	{
		int ind = ui->ImageThumbList->currentRow();

		updateImageType(ind, imageType::test);

		updateThumbs(ind);
	}
	else if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		// delete image in index check
		for (int i = checked.size() - 1; i >= 0; i--)
		{
			int ind = checked[i];

			updateImageType(ind, imageType::test);
		}

		updateThumbs();
	}
}






/**
*
*  removes image at array index
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::deleteImage
* Qualifier 
* @param     int index 
* @return    bool
* Access     public 
*/
void MainWindow::deleteImage(int index, bool bDisplay)
{
	if (index >= 0 && index < m_ImagesContainer.getNumImages())
	{
		m_ImagesContainer.removeImage(index);

		delete ui->ImageThumbList->item(index);
	}

	if (bDisplay)
	{
		if (getValidImageIndex() < 0)
			ui->display_image->m_Image = QImage();

		DisplayImage();
	}
}

/**
*
*  slot to delete current image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeleteImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeleteImage_triggered()
{
	int item;

	QObject* obj = sender();

	int ind = ui->ImageThumbList->currentRow();

	deleteImage(ind);
}

/**
*
*  slot to delete checked image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeleteObject_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeleteObject_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QObject* obj = sender();

	if (obj == ui->actionDeleteObject)
	{
		int item;
		std::vector<int> checked = getCheckedImages();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
		{
			bool changeCurrent = false;

			if (checked.size() > 1)
				qSort(checked.begin(), checked.end());

			// delete image in index check
			for (int i = checked.size() - 1; i >= 0; i--)
				deleteImage(checked[i], i==0);	// display when list finally processed
		}
		else
		{
			ui->display_image->deleteSelectedDrawingObject();
		}
		ui->display_image->repaint();
	}
	else
	{
		DBOUT("called from menu");
	}
}


/**
*
*  slot to grab image using Basler pylon supported camera
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionGrab_Image_From_Camera_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionGrab_Image_From_Camera_triggered()
{
#ifdef PYLON

#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    try
    {
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
        std::cout << "Camera Name: " << camera.GetDeviceInfo().GetModelName() << std::endl;

        CGrabResultPtr ptrGrabResult;

        camera.GrabOne(500,ptrGrabResult,TimeoutHandling_ThrowException);

        if(ptrGrabResult->GrabSucceeded())
        {
            CPylonImage target;

            CImageFormatConverter converter;
            converter.OutputPixelFormat = PixelType_BGR8packed;
            converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;

            converter.Convert(target, ptrGrabResult);

            cv::Mat image(target.GetWidth(), target.GetHeight(), CV_8UC3, target.GetBuffer(), Mat::AUTO_STEP);

            if(image.empty())
            {
                std::cout << "Unable to convert image to cv::mat" << std::endl;
                return;
            }

            std::cout << "Image captured" << std::endl;

			//m_ImagesContainer.m_Images.push_back(tim);

            addCVImage(image, "camera image");
        }
        else
        {
            std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
        }
    }
    catch (const GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred " << e.GetDescription() << std::endl;
    }
#endif
}

/**
*
*  slot to merge checked binary and normal images
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionMergeImages_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionMergeImages_triggered()
{
	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;
	bool bOK = false;
	int maskIndex = -1;

	// find which of the images is mask image
	for (int i = 0; i < checked.size(); i++)
	{
		if (m_ImagesContainer.getImageAt(checked[i]).getImageFunction() == imageType::mask)
		{
			maskIndex = checked[i];
			break;
		}
	}

	if (maskIndex >= 0)
	{
		cv::Mat& mask = m_ImagesContainer.getImageAt(maskIndex).getImage();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 1)
		{
			// delete image in index check
			for (int i = 0; i < checked.size(); i++)
			{
				if (checked[i] == maskIndex)
					continue;

				int c = m_ImagesContainer.getImageAt(checked[i]).getImageCols();
				int r = m_ImagesContainer.getImageAt(checked[i]).getImageRows();

				if (mask.rows != r || mask.cols != c)
				{
					// enlarge mask image by copying to larger image
					cv::Mat newMask;

					cv::resize(mask, newMask, m_ImagesContainer.getImageAt(checked[i]).getImageSize());

					m_ImagesContainer.getImageAt(checked[i]).getImage().copyTo(dst, newMask);
				}
				else
					m_ImagesContainer.getImageAt(checked[i]).getImage().copyTo(dst, mask);

				bOK = true;
			}
			if (bOK)
				addCVImage(dst, "masked image");
		}
	}
	else
	{
		showMessage("One of the images needs to be a binary mask image for the merging");
	}
}

/**
*
*  slot to display settings dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSettings_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSettings_triggered()
{
	m_settingsDlg.create(m_settings);

	setHistogramImage();

    if(m_settingsDlg.exec())
    {
		m_settings = m_settingsDlg.getSettings();
    }
}

/**
*
*  slot to threshold selected image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionThresholdImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionThresholdImage_triggered()
{
	int ind = getValidImageIndex();

	cv::Mat& im = m_ImagesContainer.getImageAt(ind).getImage();
	cv::Mat out;

	if(m_settings.autoThreshold)
		out = ImageProcessing::HistogramClusteringGray(im, m_settings.NoClustersThreshold);
	else
		out = ImageProcessing::Threshold(im, m_settings.threshold_min, m_settings.threshold_max);

	addCVImage(out, "threshold image", true, imageType::mask, true);
}

/**
*
*  slot to perform connected component analysis on selected image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionConnected_Components_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionConnected_Components_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage& tim = m_ImagesContainer.getImageAt(ind);

		if (tim.getImageFunction() == imageType::mask)
		{
			targeterImage ccim = getConnectedComponents(tim.getImage());

			addCVImage(ccim, "connected components image", true);
		}
		else
			showMessage(imageType::mask);
	}
}

/**
*
*  Sets connected component image structure from binary image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::getConnectedComponents
* Qualifier 
* @param     cv::Mat & im 
* @return    targeterImage&
* Access     public 
*/
targeterImage MainWindow::getConnectedComponents(cv::Mat& im)
{
	cv::Mat bin, out, stats, centroids;
	cv::Mat labels;

	const int connectivity_8 = 8;

	cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);

	// create new ccimage

	targeterImage ccim(&m_ImagesContainer);

	int nLabels = connectedComponentsWithStats(bin, labels, stats, centroids, connectivity_8, CV_32S);

	labels.convertTo(labels, CV_8U);

	normalize(labels, labels, 0, 255, NORM_MINMAX, -1, Mat());

	ccim.setLabelsImage(labels);

	cv::cvtColor(labels, bin, cv::COLOR_GRAY2BGR, 3);

	ccim.setCentroidsImage(centroids);
	ccim.setStatsImage(stats);
	ccim.setLabelsImage(labels);

	ccim.setImageType(imageType::cclabels);
	ccim.setName("labeled image");

	ccim.addImage(bin);

	return ccim;
}

/**
*
*  slot to flag images as target (training) images
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::on_actionSet_as_Target_triggered
* Qualifier
* @return    void
* Access     private
*/
void MainWindow::on_actionSet_as_Target_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (m_bContextMenuAction)
	{
		int ind = ui->ImageThumbList->currentRow();

		updateImageType(ind, imageType::target);

		updateThumbs(ind);
	}
	else if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		int ind = checked[0];

		updateImageType(ind, imageType::target);

		updateThumbs(ind);
	}
}

/**
*
*  Slot to score image of possible targets found in the detection image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionScoreImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionScoreImage_triggered()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	algoType::algoType matchType = (algoType::algoType)(m_settings.algorithmType - algoType::SQDIFF);

	QString s("score image ");

	s.append(ALGOSTRINGS(m_settings.algorithmType));

	cv::Mat im = createScoreImage();

	if (im.rows > 0)
	{
		addCVImage(im, s, true, imageType::score);
	}

	QApplication::restoreOverrideCursor();

}

/**
*
*   Slot to score image of possible targets found in the detection image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::createScoreImage
* Qualifier 
* @return    cv::Mat
* Access     public 
*/
cv::Mat MainWindow::createScoreImage()
{
	std::vector<targeterImage> targetImages;
	targeterImage testImage(&m_ImagesContainer);
	bool bFoundTest = false;

	// get vector list of training images from targeterImages
	for (int i = m_ImagesContainer.getNumImages()-1; i >=0; i--)
	{
		targeterImage& m = m_ImagesContainer.getImageAt(i);

		if (m.getImageFunction() == imageType::target)
		{
			targetImages.push_back(m);
		}
		else if (!bFoundTest && m.getImageFunction() == imageType::test)
		{
			bFoundTest = true;
			testImage = m;
		}
	}

	if (targetImages.size() > 0 && bFoundTest)
	{
		algoType::algoType matchType = (algoType::algoType)(m_settings.algorithmType - algoType::SQDIFF);

		if (m_settings.algorithmType == algoType::COOC)
		{
			return FindTargets::ColourOccuranceHistogram(targetImages, testImage, m_settings.distance, m_settings.cluster, this);
		}
		else if (m_settings.algorithmType == algoType::LAPLACIAN)
		{
			showMessage("function not yet implemented");
		}
		else
		{
			return FindTargets::CVMatching(targetImages, testImage, matchType);
		}
	}
	else
	{
		QString msg;
		if (targetImages.size() == 0)
			msg = "You need to set a target ";
		if (testImage.getImage().empty())
			msg += "and a test ";

		msg += "image first";

		showMessage(msg);

		return cv::Mat();
	}
}



/**
*
* Slot to find targets in detection image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::on_actionCreate_target_image_triggered
* Qualifier
* @return    void
* Access     private
*/
void MainWindow::on_actionFind_targets_triggered()
{

	QApplication::setOverrideCursor(Qt::WaitCursor);

	algoType::algoType matchType = (algoType::algoType)(m_settings.algorithmType - algoType::SQDIFF);

	cv::Mat im = createScoreImage();
	cv::Mat originalImage;

	for (int i = m_ImagesContainer.getNumImages()-1; i >=0; i--)
	{
		if (m_ImagesContainer.getImageAt(i).getImageFunction() == imageType::test)
		{
			originalImage = m_ImagesContainer.getImageAt(i).getImage();
			break;
		}
	}

	if (im.rows > 0)
	{
		/*addCVImage(im, s, true, imageType::score);*/

		// threshold score image
		cv::Mat out = ImageProcessing::Threshold(im, (int)255.0*double(m_settings.ScoreThreshold) / 100.0, 255);

		/*
		QString s("score image ");
		s.append(ALGOSTRINGS(m_settings.algorithmType));
		s.append(" thresholded");

		addCVImage(out, s, true, imageType::score);
		*/

		// connected components image
		targeterImage& tim = getConnectedComponents(out);

		// centroids image - original + crosses

		cv::Mat targets = originalImage.clone();

		drawCentroids(tim, targets);

		addCVImage(targets, "detected targets image", true, imageType::centroids, true);

		QFile f("targeterOutput.xml");

		qint64 s = f.size();
		if (s > 0) 
			f.open(QFile::ReadWrite);
		else
			f.open(QFile::WriteOnly);

		writeCentroids(tim, f);
	}

	QApplication::restoreOverrideCursor();
}

/**
*
*  Draws crosses at centroid positions of connected component regions on supplied cv::Mat image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::drawCentroids
* Qualifier 
* @param     targeterImage & tim 
* @param     cv::Mat & drawimage 
* @return    void
* Access     public 
*/
void MainWindow::drawCentroids(targeterImage& tim, cv::Mat& drawimage)
{
	if (tim.getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim.getCentroidsImage();
		cv::Mat& stats = tim.getStatsImage();

		for (int i = 1; i < centroidsImage.rows; i++)
		{
			double x = centroidsImage.at<double>(i, 0);
			double y = centroidsImage.at<double>(i, 1);
			int *row = &stats.at<int>(i, 0);
			cv::rectangle(drawimage, cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]), cv::Scalar(0, 255, 0));
			cv::drawMarker(drawimage, cv::Point(x, y), cv::Scalar(0, 0, 255), MARKER_CROSS, 10, 1);
		}
	}
	else
	{
		showMessage(imageType::cclabels);
	}
}

/**
*
*  Writes XML of target locations in image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::writeCentroids
* Qualifier 
* @param     targeterImage & tim 
* @param     QFile & xmlFile 
* @return    void
* Access     public 
*/
void MainWindow::writeCentroids(targeterImage& tim, QFile& xmlFile)
{
	if (tim.getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim.getCentroidsImage();
		cv::Mat& stats = tim.getStatsImage();

		QXmlStreamWriter stream;

		stream.setDevice(&xmlFile);
		stream.writeStartDocument();

		stream.writeStartElement("target_coordinates");

		for (int i = 1; i < centroidsImage.rows; i++)
		{
			double x = centroidsImage.at<double>(i, 0);
			double y = centroidsImage.at<double>(i, 1);
			int *row = &stats.at<int>(i, 0);
			double left = row[CC_STAT_LEFT];
			double top = row[CC_STAT_TOP];
			double width = row[CC_STAT_WIDTH];
			double height = row[CC_STAT_HEIGHT];

			stream.writeStartElement("target");

			stream.writeStartElement("centroid");
			stream.writeAttribute("x", QString::number(x));
			stream.writeAttribute("y", QString::number(y));
			stream.writeEndElement();

			stream.writeStartElement("bounding_rectangle");
			stream.writeAttribute("top", QString::number(top));
			stream.writeAttribute("left", QString::number(left));
			stream.writeAttribute("width", QString::number(width));
			stream.writeAttribute("height", QString::number(height));
			stream.writeEndElement();

			stream.writeEndElement();

			xmlFile.flush();
		}

		stream.writeEndElement();

		stream.writeEndDocument();

		xmlFile.close();
	}
	else
	{
		showMessage(imageType::cclabels);
	}
}

/**
*
*  Finds center coordinates of connected  component regions
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionFind_Centers_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionFind_Centers_triggered()
{
	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;

	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage& tim = m_ImagesContainer.getImageAt(ind);

		pIm = tim.getImage().clone();

		drawCentroids(tim, pIm);

		addCVImage(pIm, "detected targets image", true, imageType::centroids, true);
	}
}


void MainWindow::on_actionFilter_Binary_Objects_triggered()
{

}

/**
*
*  Inverts image black->white etc.
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionInvert_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionInvert_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(ind).getImage();
		cv::Mat out;

		bitwise_not(im, out);

		addCVImage(out, "inverted image", true, m_ImagesContainer.getImageAt(ind).getImageFunction());
	}
}


/*

void MainWindow::maskImage(QImage& im, drawingShape shape)
{
#ifdef DEBUGPRINT
qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
QPainterPath path;

if(shape.type == drawingMode::poly)
path.addPolygon(shape.polygon);
else
path.addEllipse(shape.boundingBox);

QImage cutout(im.size(), QImage::Format_ARGB32_Premultiplied);

Q_ASSERT(!cutout.isNull());

if(!cutout.isNull())
{
cutout.fill(Qt::black);

QPainter p(&cutout);
p.setClipPath(path);
p.drawImage(0, 0, im);
p.end();

im = cutout.copy();
}

}
*/

/*
void MainWindow::maskImage(QImage& im, drawingShape shape)
{

QImage cutout(im.size(), im.format());
QPainter painter(&cutout);
QPainterPath path;

qDebug() << "mask image circle" << shape.type <<endl;

if(shape.type == drawingMode::poly)
{
path.addPolygon(shape.polygon);
}
else
{
qDebug() << "mask image circle" << shape.boundingBox <<endl;

QRegion r(shape.boundingBox, QRegion::Ellipse);
painter.setClipRegion(r);
}

painter.drawImage(0, 0, im);

painter.end();
}

// goes in function below
//Mat im;

//HelperFunctions::resizeImagePreserve(*m_pCurrentImage, im, ui->display_image->width(), ui->display_image->height());

//QImage imdisplay = mat_to_qimage_ref(im);

//QImage imdisplay = m_CurrentQImage.scaled(ui->display_image->width(), ui->display_image->height(), Qt::KeepAspectRatio);

//ui->display_image->setPixmap(QPixmap::fromImage(imdisplay));

*/



