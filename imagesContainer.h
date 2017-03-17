#ifndef IMAGESCONTAINER_H
#define IMAGESCONTAINER_H

#include "targeterimage.h"

/**
class to store all images 
**/
class ImagesContainer
{
private:
	std::vector<targeterImage> m_Images;

public:
	ImagesContainer() {  };
	~ImagesContainer() { 
		m_Images.empty(); 
	};
	int getNumImages() {
		return m_Images.size(); 
	}
	targeterImage* getImageAtPtr(int i) { 
		if (i >= 0 && i < m_Images.size()) 
			return &(m_Images[i]);
	}
	targeterImage& getImageAt(int i) { 
		if (i >= 0 && i < m_Images.size()) 
			return m_Images[i]; 
	}
	targeterImage* getImageAtOfType(int i, imageType::imageType type) { 
		if (i >= 0 && i < m_Images.size()) 
			return &(m_Images[i].getImageOfType(type)); 
		return NULL;
	}
	std::vector<targeterImage> getImages() { 
		return m_Images; 
	};
	void removeImage(int ind) {
		std::vector<targeterImage>::iterator it = m_Images.begin();
		std::advance(it, ind);
		m_Images.erase(it);
	}

	void addImage(targeterImage& im) { 
		m_Images.push_back(im); 
	};

	void freeImages() { 
		foreach(targeterImage item, m_Images) 
			item.free1DImages();  
	};
};

#endif
