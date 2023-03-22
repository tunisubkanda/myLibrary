/**
 * @file rect.hpp
 * @brief cv::Rectの派生
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef MYLIBRARY_RECT_HPP
#define MYLIBRARY_RECT_HPP

#include <opencv2/core/types.hpp>

/**
 * @brief cv::Rect_<short>用
 * std::minがshortで用いてもintと判断されるためエラーが起きる場合があるため作成.
 */
namespace RECT {
template <typename _Tp>
cv::Rect_<_Tp> Overlap(const cv::Rect_<_Tp>& a, const cv::Rect_<_Tp>& b);

template <typename _Tp>
bool isOverlap(const cv::Rect_<_Tp>& a, const cv::Rect_<_Tp>& b);
};  // namespace RECT

/**
 * @brief cv::Rectの重なりを算出
 *
 * @tparam _Tp 型
 * @param a[in] Rect A
 * @param b[in] Rect B
 * @return cv::Rect_<_Tp>
 */
template <typename _Tp>
inline cv::Rect_<_Tp> RECT::Overlap(const cv::Rect_<_Tp>& a, const cv::Rect_<_Tp>& b) {
    // if(a.empty() || b.empty()) return cv::Rect_<_Tp>();
    if(!(a.width > 0 && a.height > 0 && b.width > 0 && b.height > 0)) return cv::Rect_<_Tp>();

    const cv::Rect_<_Tp>& Rx_min = (a.x < b.x) ? a : b;
    const cv::Rect_<_Tp>& Rx_max = (a.x < b.x) ? b : a;
    const cv::Rect_<_Tp>& Ry_min = (a.y < b.y) ? a : b;
    const cv::Rect_<_Tp>& Ry_max = (a.y < b.y) ? b : a;

    if((Rx_min.x < 0 && Rx_min.x + Rx_min.width < Rx_max.x) ||
        (Ry_min.y < 0 && Ry_min.y + Ry_min.height < Ry_max.y)) return cv::Rect_<_Tp>();

    cv::Rect_<_Tp> _rect(
        Rx_max.x,
        Ry_max.y,
        std::min<_Tp>(Rx_min.width - (Rx_max.x - Rx_min.x), Rx_max.width),
        std::min<_Tp>(Ry_min.height - (Ry_max.y - Ry_min.y), Ry_max.height));

    // if(_rect.empty()) return cv::Rect_<_Tp>();
    if(!(_rect.width > 0 && _rect.height > 0)) return cv::Rect_<_Tp>();
    return _rect;
}

/**
 * @brief cv::Rectの重なりの判定
 *
 * @tparam _Tp 型
 * @param a[in] Rect A
 * @param b[in] Rect B
 * @return true 重なりが存在する
 */
template <typename _Tp>
inline bool RECT::isOverlap(const cv::Rect_<_Tp>& a, const cv::Rect_<_Tp>& b) {
    // if(a.empty() || b.empty()) return false;
    if(!(a.width > 0 && a.height > 0 && b.width > 0 && b.height > 0)) return false;

    const cv::Rect_<_Tp>& Rx_min = (a.x < b.x) ? a : b;
    const cv::Rect_<_Tp>& Rx_max = (a.x < b.x) ? b : a;
    const cv::Rect_<_Tp>& Ry_min = (a.y < b.y) ? a : b;
    const cv::Rect_<_Tp>& Ry_max = (a.y < b.y) ? b : a;

    if((Rx_min.x < 0 && Rx_min.x + Rx_min.width < Rx_max.x) ||
        (Ry_min.y < 0 && Ry_min.y + Ry_min.height < Ry_max.y)) return false;

    if(std::min<_Tp>(Rx_min.width - (Rx_max.x - Rx_min.x), Rx_max.width) > 0 &&
        std::min<_Tp>(Ry_min.height - (Ry_max.y - Ry_min.y), Ry_max.height) > 0) return true;
    return false;
}

#endif /* MYLIBRARY_RECT_HPP */