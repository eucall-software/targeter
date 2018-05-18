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
	
	std::vector<targeterImage> m_Images;

	ImagesContainer() {  };
	~ImagesContainer() { 
		m_Images.empty(); 
	};

	int getNumImages() 
	{
		return (int)m_Images.size(); 
	}
	targeterImage* getImageAtPtr(int i) 
	{ 
		if (i >= 0 && i < m_Images.size())
			return &(m_Images[i]);
		else
			return NULL;
	}

	targeterImage* getLastImagePtr() 
	{
		int size = m_Images.size() - 1;

		if (size >= 0)
			return &(m_Images[m_Images.size() - 1]);
		else
			return NULL;
	}

	targeterImage& getImageAt(int i) { 
		if (i >= 0 && i < m_Images.size())
			return m_Images[i];
	}

	targeterImage* getImageAtOfType(int i, imageType::imageType type) 
	{ 
		if (i >= 0 && i < m_Images.size()) 
			return &(m_Images[m_Images[i].getFriendArrayIndexOfType(type)]);
		else
			return NULL;
		return NULL;
	}

	std::vector<targeterImage> getImages() { 
		return m_Images; 
	};

	std::vector<targeterImage> getImages(std::vector<int> indexes) {
		std::vector<targeterImage> images;

		foreach(int i,  indexes)
		{
			images.push_back(m_Images[i]);
		}

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
