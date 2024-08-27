/*
* This header file provides a set of functions for performing arithmetic operations on large strings.
* These operations can handle numbers that exceed the limits of standard integer types.
* Currently, decimal numbers are not supported, but support may be added in the future.
* The functions assume input strings consist only of digits and an optional leading minus sign.
*/
#ifndef MYSTRINGALGORITHM_HPP
#define MYSTRINGALGORITHM_HPP

#pragma warning(disable:4267)
#pragma warning(disable:4244)


#ifdef _STRING_
#ifdef _ALGORITHM_

std::string StrMinus(std::string a, std::string b) noexcept;

void RevStr(std::string& s) noexcept {
	std::reverse(s.begin(), s.end());
}
bool StrRefToNumGreater(const std::string a,const std::string b) noexcept {
	if (a[0] == b[0] && a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		std::string subb = b.substr(1, b.size() - 1);
		return (StrRefToNumGreater(subb, suba));
	}
	if (a[0] == '-') return false;
	if (b[0] == '-') return true;
	if (a.size() > b.size()) return true;
	if (a.size() < b.size()) return false;
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i]) return true;
		if (a[i] < b[i]) return false;
	}
	return false;//they are equal
}
std::string ToStr(const long long i) noexcept {
	int n = 0;
	std::string res = "";
	if (i == 0) {
		return "0";
	}
	else if (i > 0) {
		int j = i;
		while (j > 0) {
			res.push_back((char)(j % 10 + '0'));
			j /= 10;
		}
		RevStr(res);
		return res;
	}
	else {
		long long j = -1 * i;
		while (j > 0) {
			res.push_back((char)(j % 10 + '0'));
			j /= 10;
		}
		res.push_back('-');
		RevStr(res);
		return res;
	}
	return res;
}
long long ToLong(const std::string s) noexcept {
	if (s == "0") return 0;
	std::string subs;
	long long ans = 0;
	int sign = 1;
	if (s[0] == '-') {
		sign = -1;
		subs = s.substr(1, s.size() - 1);
	}
	else subs = s;
	for (char i : subs) {
		ans *= 10;
		ans += (int)(i - '0');
	}
	return ans * sign;
}long long ToLong(const wchar_t s[]) noexcept {
	if (s[0] == L'0') return 0;
	long long ans = 0;
	int sign = 1;
	int i = 0;
	if (s[0] == '-') {
		sign = -1;
		i = 1;
	}
	for (; s[i] != 0 ; i ++ ) {
		ans *= 10;
		ans += (int)(s[i] - '0');
	}
	return ans * sign;
}

std::string StrAdd(const std::string a, const std::string b) noexcept {
	if (a[0] == '-' && b[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		std::string subb = b.substr(1, b.size() - 1);
		return ("-" + StrAdd(suba, subb));
	}
	if (a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		return StrMinus(b, suba);
	}
	if (b[0] == '-') {
		std::string subb = b.substr(1, b.size() - 1);
		return StrMinus(a, subb);
	}
	if (a.size() < b.size()) return StrAdd(b, a);
	std::string ans;
	std::string stra = a, strb = b;
	RevStr(stra);
	RevStr(strb);
	int s = stra.size();
	int carry = 0;
	for (int i = 0; i < s; i++) {
		if (i < strb.size()) {
			int m = (int)(stra[i] - '0'), n = (int)(strb[i] - '0');
			int p = m + n + carry;
			carry = 0;
			if (p < 10) ans.push_back((char)(p + '0'));
			else {
				ans.push_back((char)(p - 10 + '0'));
				carry = 1;
			}
		}
		else {
			int m = (int)(stra[i] - '0') + carry;
			carry = 0;
			if (m < 10) ans.push_back((char)(m + '0'));
			else {
				ans.push_back((char)('0'));
				carry = 1;
			}
		}
	}
	if (carry == 1) ans.push_back('1');
	RevStr(ans);
	return ans;
}
std::string StrAdd(const long long a, const long long b) noexcept {
	return StrAdd(ToStr(a), ToStr(b));
}
std::string StrAdd(const long long a, const std::string b) noexcept {
	return StrAdd(ToStr(a), b);
}
std::string StrAdd(const std::string a, const long long b) noexcept {
	return StrAdd(a, ToStr(b));
}

std::string StrMultiply(const std::string a, const std::string b) noexcept {
	if (b[0] == '-') {
		std::string subb = b.substr(1, b.size() - 1);
		if (a[0] == '-') {
			std::string suba = a.substr(1, a.size() - 1);
			return StrMultiply(suba, subb);
		}
		return "-" + StrMultiply(a, subb);
	}
	if (b.size() > a.size()) return StrMultiply(b, a);
	std::string ans = "0", stra = a, strb = b;
	RevStr(strb);
	std::vector<std::string> singles;
	for (int i = 0; i < strb.size(); i++) {
		std::string str = "0";
		int k = (int)(strb[i] - '0');
		for (int j = 0; j < k; j++) {
			str = StrAdd(str, stra);
		}
		for (int l = 0; l < i; l++) {
			str.push_back('0');
		}
		singles.push_back(str);
	}
	for (int p = 0; p < singles.size(); p++) {
		ans = StrAdd(ans, singles[p]);
	}
	return ans;
}
std::string StrMultiply(const long long a, const long long b) noexcept {
	return StrMultiply(ToStr(a), ToStr(b));
}
std::string StrMultiply(const long long a, const std::string b) noexcept {
	return StrMultiply(ToStr(a), b);
}
std::string StrMultiply(const std::string a, const long long b) noexcept {
	return StrMultiply(a, ToStr(b));
}

std::string StrMinus(const std::string a, const std::string b) noexcept {
	if (a == b) return "0";
	if (b[0] == '-') {
		std::string str = b.substr(1, b.size() - 1);
		return StrAdd(a, str);
	}
	if (a[0] == '-') {
		std::string str = a.substr(1, a.size() - 1);
		std::string ans = "-" + StrAdd(str, b);
		return ans;
	}
	if (!StrRefToNumGreater(a, b)) {
		return "-" + StrMinus(b, a);
	}
	std::string ans = "", stra = a, strb = b;
	RevStr(stra);
	RevStr(strb);
	int s = stra.size();
	int subtract = 0;
	for (int i = 0; i < s; i++) {
		if (i < strb.size()) {
			int k = stra[i] - strb[i] - subtract;
			subtract = 0;
			if (k < 0) {
				subtract = 1;
				k += 10;
			}
			ans.push_back((char)(k + '0'));
		}
		else {
			int k = stra[i] - subtract - '0';
			subtract = 0;
			if (k < 0) {
				subtract = 1;
				k += 10;
			}
			ans.push_back((char)(k + '0'));
		}
	}
	while (ans[ans.size() - 1] == '0') {
		ans.pop_back();
	}
	RevStr(ans);
	return ans;
}
std::string StrMinus(const long long a, const long long b) noexcept {
	return StrMinus(ToStr(a), ToStr(b));
}
std::string StrMinus(const long long a, const std::string b) noexcept {
	return StrMinus(ToStr(a), b);
}
std::string StrMinus(const std::string a, const long long b) noexcept {
	return StrMinus(a, ToStr(b));
}

//don't put "0" in the divisor or it will return "0"
std::string StrDivide(const std::string a, const std::string b) noexcept {
	if (b == "0") return "0";
	if (a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		if (b[0] == '-') {
			std::string subb = b.substr(1, b.size() - 1);
			return StrDivide(suba, subb);
		}
		return "-" + StrDivide(suba, b);
	}
	if (b[0] == '-') {
		std::string subb = b.substr(1, b.size() - 1);
		return "-" + StrDivide(a, subb);
	}
	std::string ans = "0", c = a;
	while (StrRefToNumGreater(c, "0")) {
		c = StrMinus(c, b);
		ans = StrAdd(ans, "1");
	}
	if (StrRefToNumGreater("0", c)) {
		ans = StrMinus(ans, "1");
	}
	return ans;
}
std::string StrDivide(const long long a, const long long b) noexcept {
	return StrDivide(ToStr(a), ToStr(b));
}
std::string StrDivide(const long long a, const std::string b) noexcept {
	return StrDivide(ToStr(a), b);
}
std::string StrDivide(const std::string a, const long long b) noexcept {
	return StrDivide(a, ToStr(b));
}

std::string StrMod(const std::string a, const std::string b) noexcept {
	std::string c = a;
	while (StrRefToNumGreater(c, "0")) {
		c = StrMinus(c, b);
	}
	if (c == "0") return c;
	return StrAdd(c, b);
}
std::string StrMod(const long long a, const long long b) noexcept {
	return StrMod(ToStr(a), ToStr(b));
}
std::string StrMod(const long long a, const std::string b) noexcept {
	return StrMod(ToStr(a), b);
}
std::string StrMod(const std::string a, const long long b) noexcept {
	return StrMod(a, ToStr(b));
}

std::string StrPow(const std::string x, const std::string n) noexcept {
	if (x[0] == '-') {
		std::string subx = x.substr(1, x.size() - 1);
		return (StrMod(n, "2") == "0") ? (StrPow(subx, n)) : ("-" + StrPow(subx, n));
	}
	if (StrRefToNumGreater("0",n)) return "0";
	if (n == "0") return "1";
	std::string k = StrPow(x, StrDivide(n, "2"));
	return ((StrMod(n, "2") != "0") ? StrMultiply(StrMultiply(x, k), k) : StrMultiply(k, k));
}
std::string StrPow(const long long a, const long long b) noexcept {
	return StrPow(ToStr(a), ToStr(b));
}
std::string StrPow(const long long a, const std::string b) noexcept {
	return StrPow(ToStr(a), b);
}
std::string StrPow(const std::string a, const long long b) noexcept {
	return StrPow(a, ToStr(b));
}

std::string StrSqrt(const std::string x) noexcept {
	if (x[0] == '-') return "-1";
	std::string s = "0";
	for (; !StrRefToNumGreater(s, x); s = StrAdd(s, "1")) {
		std::string pow = StrPow(s, "2"), pow1 = StrPow(StrAdd(s, "1"), "2");
		if (x == pow || (StrRefToNumGreater(x, pow) && StrRefToNumGreater(pow1, x))) {
			return s;
		}
	}
	return "0";//will never happen
}
std::string StrSqrt(const long long a) noexcept {
	return StrSqrt(ToStr(a));
}

std::string StrAbs(const std::string x) noexcept {
	return (x[0] != '-') ? x : x.substr(1, x.size() - 1);
}
std::string StrAbs(const long long a) noexcept {
	return StrAbs(ToStr(a));
}

char* ToC(const std::string str) noexcept {
	char* res = new char[str.size() + 1];
	for (int i = 0; i < str.size(); i++) {
		res[i] = str[i];
	}
	res[str.size()] = '\0';
	return res;
}
char* ToC(const long long a) noexcept {
	return ToC(ToStr(a));
}
#else
_EMIT_STL_WARNING(SA0002, "<algorithm> isn't included. Functions is \"MyStringAlgorithm.hpp\" cannot be used");
#endif//algorithm
#else
_EMIT_STL_WARNING(SA0001, "<string> isn't included. Functions is \"MyStringAlgorithm.hpp\" cannot be used");
#ifndef _ALGORITHM_
_EMIT_STL_WARNING(SA0002, "<algorithm> isn't included. Functions is \"MyStringAlgorithm.hpp\" cannot be used");
#endif
#endif//string

int longsize(const long long i) noexcept {
	int n = 0;
	if (i > 0) {
		long long j = i;
		while (j > 0) {
			j = j / 10;
			++n;
		}
	}
	else if (i < 0) {
		long long j = -1 * i;
		while (j > 0) {
			j = j / 10;
			++n;
		}
	}
	if (n == 0) n = 1;
	return n;
}
wchar_t* ToW(const long long i) noexcept {
	int n = 0;
	wchar_t* res;
	if (i == 0) {
		res = new wchar_t[2];
		res[0] = L'0';
		res[1] = L'\0';
		return res;
	}
	else if (i > 0) {
		long long j = i;
		while (j > 0) {
			j = j / 10;
			++n;
		}
		res = new wchar_t[n + 1];
		res[n] = L'\0';
		j = i;
		for (int k = n - 1; k > -1; --k) {
			res[k] = (wchar_t)(j % 10 + L'0');
			j /= 10;
		}
		return res;
	}
	else {
		long long j = -1 * i;
		while (j > 0) {
			j = j / 10;
			++n;
		}
		res = new wchar_t[n + 2];
		res[n + 1] = L'\0';
		res[0] = L'-';
		j = -1 * i;
		for (int k = n; k > 0; --k) {
			res[k] = (wchar_t)(j % 10 + L'0');
			j /= 10;
		}
		return res;

	}
	return res;
}
#ifdef _WINDOWS_
wchar_t* ToW(const char* ori) noexcept {
	wchar_t* res;
	int len = MultiByteToWideChar(CP_ACP, 0, ori, strlen(ori), 0, 0);
	res = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, ori, strlen(ori), res, len);
	res[len] = '\0';
	return res;
}
//using this, you can calculate numbers like:
//ToW(MyAdd("2","3"))
//return:(wchar_t*)L"5"
#ifdef _STRING_
wchar_t* ToW(const std::string& a) noexcept {
	char* mid = new char[a.size() + 1];
	for (int i = 0; i <= a.size(); i++) {
		mid[i] = a[i];
	}
	return ToW(mid);
}
#endif//string
#else
_EMIT_STL_WARNING(TOW0001, "<Windows.h> isn't included. Some of the functions such as from char[] to wchar_t[] cannot work.");
#endif // windows
#ifdef _STRING_
wchar_t* ToW(const std::wstring& a) noexcept {
	wchar_t* ans = new wchar_t[a.size() + 1];
	for (int i = 0; i <= a.size(); i++) {
		ans[i] = a[i];
	}
	return ans;
}
#else
_EMIT_STL_WARNING(TOW0002, "<string> isn't included. Some of the functions such as from string to wchar_t[] cannot work.");
#endif//string


#pragma warning(default:4267)
#pragma warning(default:4244)

#endif // MYSTRINGALGORITHM_HPP
