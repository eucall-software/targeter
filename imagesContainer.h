// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef IMAGESCONTAINER_H
#define IMAGESCONTAINER_H

#include "targeterimage.h"

/**
class to store all images 
**/
class ImagesContainer
{
private:
	
public:
	
	QVector<QExplicitlySharedDataPointer<targeterImage>> m_Images;	/// collection of all images

	ImagesContainer() {  };
	~ImagesContainer() { 
		m_Images.empty(); 
	};

	int getNumImages() 
	{
		return (int)m_Images.size(); 
	}
	
	QExplicitlySharedDataPointer<targeterImage> getLastImagePtr()
	{
		int size = m_Images.size() - 1;

		if (size >= 0)
			return m_Images[m_Images.size() - 1];
	}

	QExplicitlySharedDataPointer<targeterImage> getImageAt(int i) {
		if (i >= 0 && i < m_Images.size())
			return m_Images[i];
		else
			return QExplicitlySharedDataPointer<targeterImage>();
	}

	QVector<QExplicitlySharedDataPointer<targeterImage>> getImages() {
		return m_Images; 
	};

	QVector<QExplicitlySharedDataPointer<targeterImage>> getImages(std::vector<int> indexes)
	{
		QVector<QExplicitlySharedDataPointer<targeterImage>> images;

		foreach(int i,  indexes)
		{
			images.push_back(m_Images[i]);
		}

		return m_Images;
	};

	void removeImage(int ind) 
	{
		QVector<QExplicitlySharedDataPointer<targeterImage>>::iterator it = m_Images.begin();
		std::advance(it, ind);
		m_Images.erase(it);
	}

	void addImage(QExplicitlySharedDataPointer<targeterImage> im) {
		m_Images.append(im); 
	};

	void freeImages() { 
		foreach(QExplicitlySharedDataPointer<targeterImage> item, m_Images)
			item.data()->free1DImages();  
	};
};

#endif
