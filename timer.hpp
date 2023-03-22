/**
 * @file time.hpp
 * @brief 時間計測一式
 * @version 1.0
 * @date 2023-03-22
 */
#ifndef MYLIBRARY_TIME_HPP
#define MYLIBRARY_TIME_HPP

#include <chrono>
#include <cstdint>

namespace CLOCK = std::chrono;

/**
 * @brief 時間計測ベース
 *
 * @tparam T 返り値の型
 * @tparam U 保持値の型
 * @tparam V 計測精度の型
 */
template <class T, class U, class V>
class TimerClass {
    CLOCK::system_clock::time_point m_start;
    CLOCK::system_clock::time_point m_stop;

protected:
    U m_speed;

    virtual T digitAdapter() const noexcept;

public:
    TimerClass() noexcept;

    T getSpeed() const noexcept;
    T getLap() noexcept;
    void process_time(const bool flag = true) noexcept;
};

template <class T, class U, class V>
inline TimerClass<T, U, V>::TimerClass() noexcept {
    this->m_start = CLOCK::system_clock::now();
    this->m_speed = 0;
    this->m_stop = CLOCK::system_clock::now();
}

/**
 * @brief 計測時間の桁数を調整 オ-バ-ライド用
 */
template <class T, class U, class V>
inline T TimerClass<T, U, V>::digitAdapter() const noexcept {
    return static_cast<T>(m_speed);
}

/**
 * @brief 計測時間の取得
 *
 * @return T 計測時間
 */
template <class T, class U, class V>
inline T TimerClass<T, U, V>::getSpeed() const noexcept {
    return digitAdapter();
}

/**
 * @brief ラップ時間
 * 
 * @return T ラップタイム
 */
template <class T, class U, class V>
inline T TimerClass<T, U, V>::getLap() noexcept {
    m_stop = CLOCK::system_clock::now();
    m_speed = static_cast<U>(CLOCK::duration_cast<V>(m_stop - m_start).count());
    return digitAdapter();
}

/**
 * @brief 時間計測関数
 *
 * @param flag[in] 初期化
 */
template <class T, class U, class V>
inline void TimerClass<T, U, V>::process_time(const bool flag) noexcept {
    if(m_stop < m_start) {
        m_stop = CLOCK::system_clock::now();
        m_speed += static_cast<U>(CLOCK::duration_cast<V>(m_stop - m_start).count());
    } else {
        if(flag) m_speed = 0;
        m_start = CLOCK::system_clock::now();
    }
}

/**
 * @brief 最小単位0.01msで計測
 */
class XUSTimer : public TimerClass<float, std::uint32_t, CLOCK::microseconds> {
private:
    float digitAdapter() const noexcept override {
        return static_cast<float>((m_speed / 10) / 100.0f);
    }
};

//-------------------------------------------------------------------------------------
/*********************************** default class ***********************************/
//-------------------------------------------------------------------------------------

/**
 * @brief 最小単位1msで計測
 */
class MSTimer : public TimerClass<std::uint64_t, std::uint64_t, CLOCK::milliseconds> {};

/**
 * @brief 最小単位1secで計測
 */
class STimer : public TimerClass<std::uint64_t, std::uint64_t, CLOCK::seconds> {};

/**
 * @brief 最小単位1minで計測
 */
class MinTimer : public TimerClass<std::uint64_t, std::uint64_t, CLOCK::minutes> {};

#endif /* MYLIBRARY_TIME_HPP */