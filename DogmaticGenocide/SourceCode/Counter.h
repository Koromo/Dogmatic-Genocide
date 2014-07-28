#pragma once;

class Counter{
private:
	int cnt;

public:
	Counter(int cnt = 0) : cnt(cnt){ }
	Counter(const Counter& other) : cnt(other.cnt){ }
	operator int(){ return static_cast<int>(cnt); }
	operator float(){ return static_cast<float>(cnt); }
	operator double(){ return static_cast<double>(cnt); }
	bool operator==(const Counter& other){ return this->cnt == other.cnt; }
	bool operator!=(const Counter& other){ return this->cnt != other.cnt; }
	bool operator>(const Counter& other) { return this->cnt > other.cnt; }
	bool operator>=(const Counter& other){ return this->cnt >= other.cnt; }
	bool operator<(const Counter& other) { return this->cnt < other.cnt; }
	bool operator<=(const Counter& other){ return this->cnt <= other.cnt; }
	int operator+(const Counter& other){ return this->cnt + other.cnt; }
	int operator-(const Counter& other){ return this->cnt - other.cnt; }
	int operator*(const Counter& other){ return this->cnt * other.cnt; }
	int operator/(const Counter& other){ return this->cnt / other.cnt; }
	int operator%(const Counter& other){ return this->cnt % other.cnt; }
	int operator=(const Counter& other) { return this->cnt = other.cnt; }
	int operator+=(const Counter& other){ return this->cnt += other.cnt; }
	int operator-=(const Counter& other){ return this->cnt -= other.cnt; }
	int operator*=(const Counter& other){ return this->cnt *= other.cnt; }
	int operator/=(const Counter& other){ return this->cnt /= other.cnt; }
	int operator%=(const Counter& other){ return this->cnt %= other.cnt; }
	bool operator==(const int n){ return cnt == n; }
	bool operator!=(const int n){ return cnt != n; }
	bool operator>(const int n) { return cnt > n; }
	bool operator>=(const int n){ return cnt >= n; }
	bool operator<(const int n) { return cnt < n; }
	bool operator<=(const int n){ return cnt <= n; }
	int operator+(const int n){ return cnt + n; }
	int operator-(const int n){ return cnt - n; }
	int operator*(const int n){ return cnt * n; }
	int operator/(const int n){ return cnt / n; }
	int operator%(const int n){ return cnt % n; }
	int operator=(const int n) { return cnt = n; }
	int operator+=(const int n){ return cnt += n; }
	int operator-=(const int n){ return cnt -= n; }
	int operator*=(const int n){ return cnt *= n; }
	int operator/=(const int n){ return cnt /= n; }
	int operator%=(const int n){ return cnt %= n; }
	int operator++(){ return ++cnt; }
	int operator--(){ return --cnt; }
	int operator++(int n){ return cnt++; }
	int operator--(int n){ return cnt--; }
	int get() const{ return cnt; }
};

inline bool operator==(int n, const Counter& cnt){ return n == cnt.get(); }
inline bool operator!=(int n, const Counter& cnt){ return n != cnt.get(); }
inline bool operator>(int n, const Counter& cnt) { return n > cnt.get(); }
inline bool operator>=(int n, const Counter& cnt){ return n >= cnt.get(); }
inline bool operator<(int n, const Counter& cnt) { return n < cnt.get(); }
inline bool operator<=(int n, const Counter& cnt){ return n <= cnt.get(); }
inline int operator+(int n, const Counter& cnt){ return n + cnt.get(); }
inline int operator-(int n, const Counter& cnt){ return n - cnt.get(); }
inline int operator*(int n, const Counter& cnt){ return n * cnt.get(); }
inline int operator/(int n, const Counter& cnt){ return n / cnt.get(); }
inline int operator%(int n, const Counter& cnt){ return n % cnt.get(); }
inline int operator+=(int n, const Counter& cnt){ return n += cnt.get(); }
inline int operator-=(int n, const Counter& cnt){ return n -= cnt.get(); }
inline int operator*=(int n, const Counter& cnt){ return n *= cnt.get(); }
inline int operator/=(int n, const Counter& cnt){ return n /= cnt.get(); }
inline int operator%=(int n, const Counter& cnt){ return n %= cnt.get(); }
inline int operator-(const Counter& cnt){ return 0 - cnt.get(); }