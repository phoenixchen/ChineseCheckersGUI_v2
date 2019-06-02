#pragma once

//#define OPENCV_CVX_TEXT_HPP_
 
// source from: http://www.opencv.org.cn/forum.php?mod=viewthread&tid=2083&extra=&page=1
// ���OpenCV����~�r��J
 
#include <ft2build.h>
#include FT_FREETYPE_H
 
#include <opencv2/opencv.hpp>
 
class CvxText {
public:
  /**
  * �˸��r�w���
  */
  CvxText(const char* freeType);
  virtual ~CvxText();
 
  /**
  * ����r��.�ثe���ǰѼƩ|�����.
  *
  * \param font        �r������, �ثe�����
  * \param size        �r��j�p/�ťդ��/���j���/���ਤ��
  * \param underline   �U�e�u
  * \param diaphaneity �z����
  *
  * \sa setFont, restoreFont
  */
  void getFont(int* type, cv::Scalar* size=nullptr, bool* underline=nullptr, float* diaphaneity=nullptr);
 
  /**
  * �]�m�r��.�ثe���ǰѼƩ|�����.
  *
  * \param font        �r������, �ثe�����
  * \param size        �r��j�p/�ťդ��/���j���/���ਤ��
  * \param underline   �U�e�u
  * \param diaphaneity �z����
  *
  * \sa getFont, restoreFont
  */
  void setFont(int* type, cv::Scalar* size=nullptr, bool* underline=nullptr, float* diaphaneity=nullptr);
 
  /**
  * ��_��l���r��]�m.
  *
  * \sa getFont, setFont
  */
  void restoreFont();
 
  /**
  * ��X�~�r(�C���q�{���¦�).�J�줣���X���r�űN����.
  *
  * \param img  ��X���v��
  * \param text �奻���e
  * \param pos  �奻��m
  *
  * \return ��^���\��X���r�Ū��סA���Ѫ�^-1.
  */
  int putText(cv::Mat& img, char* text, cv::Point pos);
 
  /**
  * ��X�~�r(�C���q�{���¦�).�J�줣���X���r�űN����.
  *
  * \param img  ��X���v��
  * \param text �奻���e
  * \param pos  �奻��m
  *
  * \return ��^���\��X���r�Ū��סA���Ѫ�^-1.
  */
  int putText(cv::Mat& img, const wchar_t* text, cv::Point pos);
 
  /**
  * ��X�~�r.�J�줣���X���r�űN����.
  *
  * \param img   ��X���v��
  * \param text  �奻���e
  * \param pos   �奻��m
  * \param color �奻�C��
  *
  * \return ��^���\��X���r�Ū��סA���Ѫ�^-1.
  */
  int putText(cv::Mat& img, const char* text, cv::Point pos, cv::Scalar color);
 
  /**
  * ��X�~�r.�J�줣���X���r�űN����.
  *
  * \param img   ��X���v��
  * \param text  �奻���e
  * \param pos   �奻��m
  * \param color �奻�C��
  *
  * \return ��^���\��X���r�Ū��סA���Ѫ�^-1.
  */
  int putText(cv::Mat& img, const wchar_t* text, cv::Point pos, cv::Scalar color);

private:
  // �T��copy
  CvxText& operator=(const CvxText&);
  // ��X��e�r��, ��sm_pos��m
  void putWChar(cv::Mat& img, wchar_t wc, cv::Point& pos, cv::Scalar color);
 
  FT_Library   m_library;   // �r�w
  FT_Face      m_face;      // �r��
 
  // �q�{���r���X�Ѽ�
  int         m_fontType;
  cv::Scalar   m_fontSize;
  bool      m_fontUnderline;
  float      m_fontDiaphaneity;
};

int ToWchar(char* &src, wchar_t* &dest);


CvxText DrawTextSmallInit(void);
CvxText DrawTextBigInit(void);
wchar_t* DrawTextChangeStr(char* str);
void DrawTextOnWindow(cv::Mat frame,CvxText *text,wchar_t* w_str,float x,float y,int b,int g,int r);