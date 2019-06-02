#pragma once

//#define OPENCV_CVX_TEXT_HPP_
 
// source from: http://www.opencv.org.cn/forum.php?mod=viewthread&tid=2083&extra=&page=1
// 支持OpenCV中文漢字輸入
 
#include <ft2build.h>
#include FT_FREETYPE_H
 
#include <opencv2/opencv.hpp>
 
class CvxText {
public:
  /**
  * 裝載字庫文件
  */
  CvxText(const char* freeType);
  virtual ~CvxText();
 
  /**
  * 獲取字體.目前有些參數尚不支持.
  *
  * \param font        字體類型, 目前不支持
  * \param size        字體大小/空白比例/間隔比例/旋轉角度
  * \param underline   下畫線
  * \param diaphaneity 透明度
  *
  * \sa setFont, restoreFont
  */
  void getFont(int* type, cv::Scalar* size=nullptr, bool* underline=nullptr, float* diaphaneity=nullptr);
 
  /**
  * 設置字體.目前有些參數尚不支持.
  *
  * \param font        字體類型, 目前不支持
  * \param size        字體大小/空白比例/間隔比例/旋轉角度
  * \param underline   下畫線
  * \param diaphaneity 透明度
  *
  * \sa getFont, restoreFont
  */
  void setFont(int* type, cv::Scalar* size=nullptr, bool* underline=nullptr, float* diaphaneity=nullptr);
 
  /**
  * 恢復原始的字體設置.
  *
  * \sa getFont, setFont
  */
  void restoreFont();
 
  /**
  * 輸出漢字(顏色默認為黑色).遇到不能輸出的字符將停止.
  *
  * \param img  輸出的影像
  * \param text 文本內容
  * \param pos  文本位置
  *
  * \return 返回成功輸出的字符長度，失敗返回-1.
  */
  int putText(cv::Mat& img, char* text, cv::Point pos);
 
  /**
  * 輸出漢字(顏色默認為黑色).遇到不能輸出的字符將停止.
  *
  * \param img  輸出的影像
  * \param text 文本內容
  * \param pos  文本位置
  *
  * \return 返回成功輸出的字符長度，失敗返回-1.
  */
  int putText(cv::Mat& img, const wchar_t* text, cv::Point pos);
 
  /**
  * 輸出漢字.遇到不能輸出的字符將停止.
  *
  * \param img   輸出的影像
  * \param text  文本內容
  * \param pos   文本位置
  * \param color 文本顏色
  *
  * \return 返回成功輸出的字符長度，失敗返回-1.
  */
  int putText(cv::Mat& img, const char* text, cv::Point pos, cv::Scalar color);
 
  /**
  * 輸出漢字.遇到不能輸出的字符將停止.
  *
  * \param img   輸出的影像
  * \param text  文本內容
  * \param pos   文本位置
  * \param color 文本顏色
  *
  * \return 返回成功輸出的字符長度，失敗返回-1.
  */
  int putText(cv::Mat& img, const wchar_t* text, cv::Point pos, cv::Scalar color);

private:
  // 禁止copy
  CvxText& operator=(const CvxText&);
  // 輸出當前字符, 更新m_pos位置
  void putWChar(cv::Mat& img, wchar_t wc, cv::Point& pos, cv::Scalar color);
 
  FT_Library   m_library;   // 字庫
  FT_Face      m_face;      // 字體
 
  // 默認的字體輸出參數
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