#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>
#include <cmath>
 
#include "CvxText.h"
 
// 打開字庫
CvxText::CvxText(const char* freeType)
{
	assert(freeType != NULL);
	
	// 打開字庫文件, 創建一個字體
	if(FT_Init_FreeType(&m_library)) throw;
	if(FT_New_Face(m_library, freeType, 0, &m_face)) throw;
	
	// 設置字體輸出參數
	restoreFont();
	
	// 設置C語言的字符集環境
	setlocale(LC_ALL, "");
}
 
// 釋放FreeType資源
CvxText::~CvxText()
{
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}
 
// 設置字體參數:
//
// font         - 字體類型, 目前不支持
// size         - 字體大小/空白比例/間隔比例/旋轉角度
// underline   - 下畫線
// diaphaneity   - 透明度
void CvxText::getFont(int* type, cv::Scalar* size, bool* underline, float* diaphaneity)
{
	if (type) *type = m_fontType;
	if (size) *size = m_fontSize;
	if (underline) *underline = m_fontUnderline;
	if (diaphaneity) *diaphaneity = m_fontDiaphaneity;
}
 
void CvxText::setFont(int* type, cv::Scalar* size, bool* underline, float* diaphaneity)
{
	// 參數合法性檢查
	if (type) {
		if(type >= 0) m_fontType = *type;
	}
	if (size) {
		m_fontSize.val[0] = std::fabs(size->val[0]);
		m_fontSize.val[1] = std::fabs(size->val[1]);
		m_fontSize.val[2] = std::fabs(size->val[2]);
		m_fontSize.val[3] = std::fabs(size->val[3]);
	}
	if (underline) {
		m_fontUnderline   = *underline;
	}
	if (diaphaneity) {
		m_fontDiaphaneity = *diaphaneity;
	}
 
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}
 
// 恢復原始的字體設置
void CvxText::restoreFont()
{
	m_fontType = 0;            // 字體類型(不支持)
	
	m_fontSize.val[0] = 20;      // 字體大小
	m_fontSize.val[1] = 0.5;   // 空白字符大小比例
	m_fontSize.val[2] = 0.1;   // 間隔大小比例
	m_fontSize.val[3] = 0;      // 旋轉角度(不支持)
	
	m_fontUnderline   = false;   // 下畫線(不支持)
	
	m_fontDiaphaneity = 1.0;   // 色彩比例(可產生透明效果)
	
	// 設置字符大小
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}
 
// 輸出函數(顏色默認為白色)
int CvxText::putText(cv::Mat& img, char* text, cv::Point pos)
{
	return putText(img, text, pos, CV_RGB(255, 255, 255));
}
 
int CvxText::putText(cv::Mat& img, const wchar_t* text, cv::Point pos)
{
	return putText(img, text, pos, CV_RGB(255,255,255));
}
 
int CvxText::putText(cv::Mat& img, const char* text, cv::Point pos, cv::Scalar color)
{
	if (img.data == nullptr) return -1;
	if (text == nullptr) return -1;
	
	int i;
	for (i = 0; text[i] != '\0'; ++i) {
		wchar_t wc = text[i];
		
		// 解析雙字節符號
		if(!isascii(wc)) mbtowc(&wc, &text[i++], 2);
		
		// 輸出當前的字符
		putWChar(img, wc, pos, color);
	}
 
	return i;
}
 
int CvxText::putText(cv::Mat& img, const wchar_t* text, cv::Point pos, cv::Scalar color)
{
	if (img.data == nullptr) return -1;
	if (text == nullptr) return -1;
 
	int i;
	for(i = 0; text[i] != '\0'; ++i) {
		// 輸出當前的字符
		putWChar(img, text[i], pos, color);
	}
 
	return i;
}
 
// 輸出當前字符, 更新m_pos位置
void CvxText::putWChar(cv::Mat& img, wchar_t wc, cv::Point& pos, cv::Scalar color)
{
	// 根據unicode生成字體的二值位圖
	FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
	FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);
 
	FT_GlyphSlot slot = m_face->glyph;
 
	// 行列數
	int rows = slot->bitmap.rows;
	int cols = slot->bitmap.width;
 
	for (int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			int off  = i * slot->bitmap.pitch + j/8;
			
			if (slot->bitmap.buffer[off] & (0xC0 >> (j%8))) {
				int r = pos.y - (rows-1-i);
				int c = pos.x + j;
				
				if(r >= 0 && r < img.rows && c >= 0 && c < img.cols) {
					cv::Vec3b pixel = img.at<cv::Vec3b>(cv::Point(c, r));
					cv::Scalar scalar = cv::Scalar(pixel.val[0], pixel.val[1], pixel.val[2]);
				
					// 進行色彩融合
					float p = m_fontDiaphaneity;
					for (int k = 0; k < 4; ++k) {
						scalar.val[k] = scalar.val[k]*(1-p) + color.val[k]*p;
					}
 
					img.at<cv::Vec3b>(cv::Point(c, r))[0] = (unsigned char)(scalar.val[0]);
					img.at<cv::Vec3b>(cv::Point(c, r))[1] = (unsigned char)(scalar.val[1]);
					img.at<cv::Vec3b>(cv::Point(c, r))[2] = (unsigned char)(scalar.val[2]);
				}
			}
		}
	}
	
	// 修改下一個字的輸出位置
	double space = m_fontSize.val[0]*m_fontSize.val[1];
	double sep   = m_fontSize.val[0]*m_fontSize.val[2];
	
	pos.x += (int)((cols? cols: space) + sep);
}


int ToWchar(char* &src, wchar_t* &dest)
{
	if (src == NULL) {
	dest = NULL;
	return 0;
	}

	//根據環境變量設置locale(for linux)
	//const char *locale = "zh_TW.utf8";
	//setlocale(LC_CTYPE, locale);

	// 得到轉化為需要的寬字符大小
	int w_size = mbstowcs(NULL, src, 0) + 1;

	// w_size = 0 說明mbstowcs返回值為-1。即在運行過程中遇到了非法字符(很有可能使locale
	// 沒有設置正確)
	if (w_size == 0) {
	dest = NULL;
	return -1;
	}

	//wcout << "w_size" << w_size << endl;
	dest = new wchar_t[w_size];
	if (!dest) {
		return -1;
	}

	int ret = mbstowcs(dest, src, strlen(src)+1);
	if (ret <= 0) {
	return -1;
	}
	return 0;
}


CvxText DrawTextSmallInit(void){
	CvxText text("assets/kttf.ttf");
	cv::Scalar size1{ 30, 0.5, 0.1, 0 };
	text.setFont(nullptr, &size1, nullptr, 0);
	return text;
}

CvxText DrawTextBigInit(void){
	CvxText text("assets/kttf.ttf");
	cv::Scalar size2{ 40, 0.5, 0.1, 0 };
	text.setFont(nullptr, &size2, nullptr, 0);
	return text;
}

wchar_t* DrawTextChangeStr(char* str){
	wchar_t *w_str;
	ToWchar(str,w_str);
	return w_str;
}

void DrawTextOnWindow(cv::Mat frame,CvxText *text,wchar_t* w_str,float x,float y,int b,int g,int r){
	(*text).putText(frame, w_str, cv::Point(x,y),cv::Scalar(b,g,r));
	free(w_str);
}