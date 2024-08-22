/*
* The file is for counting numbers that overflow int and long.
* It cannot calculate demicals though, but I will add it soon(maybe not too soon)
*/
#ifndef MYSTRINGALGORITHM_HPP
#define MYSTRINGALGORITHM_HPP
#include <string>
#include<algorithm>

#pragma warning(disable:4267)

std::string MyMinus(std::string a, std::string b);
void RevStr(std::string& s) {
	std::reverse(s.begin(), s.end());
}
bool StrRefToNumGreater(std::string a, std::string b) {
	if (a[0] == '-' && b[0] != '-') return false;
	if (a[0] != '-' && b[0] == '-') return true;
	if (a == b) return false;
	if (a[0] == b[0] && a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		std::string subb = b.substr(1, b.size() - 1);
		return (StrRefToNumGreater(subb, suba));
	}
	if (a.size() > b.size()) return true;
	if (a.size() < b.size()) return false;
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i]) return true;
		if (a[i] < b[i]) return false;
	}
	return false;
}

std::string MyAdd(std::string a, std::string b) {
	if (a[0] == '-') {
		std::string suba = a.substr(1, a.size() - 1);
		return MyMinus(b, suba);
	}
	if (b[0] == '-') {
		std::string subb = b.substr(1, b.size() - 1);
		return MyMinus(a, subb);
	}
	if (a.size() < b.size()) return MyAdd(b, a);
	std::string ans;
	RevStr(a);
	RevStr(b);
	int s = a.size();
	int carry = 0;
	for (int i = 0; i < s; i++) {
		if (i < b.size()) {
			int m = (int)(a[i] - '0'), n = (int)(b[i] - '0');
			int p = m + n + carry;
			carry = 0;
			if (p < 10) ans.push_back((char)(p + '0'));
			else {
				ans.push_back((char)(p - 10 + '0'));
				carry = 1;
			}
		}
		else {
			int m = (int)(a[i] - '0') + carry;
			carry = 0;
			if (m < 10) ans.push_back((char)(m + '0'));
			else {
				ans.push_back((char)(m - 10 + '0'));
				carry = 1;
			}
		}
	}
	if (carry == 1) ans.push_back('1');
	RevStr(ans);
	RevStr(a);
	RevStr(b);
	return ans;
}
std::string MyMultiply(std::string a, std::string b) {
	if (b.size() > a.size()) return MyMultiply(b, a);
	std::string ans = "0";
	RevStr(b);
	std::vector<std::string> singles;
	for (int i = 0; i < b.size(); i++) {
		std::string str = "0";
		int k = (int)(b[i] - '0');
		for (int j = 0; j < k; j++) {
			str = MyAdd(str, a);
		}
		for (int l = 0; l < i; l++) {
			str.push_back('0');
		}
		singles.push_back(str);
	}
	for (int p = 0; p < singles.size(); p++) {
		ans = MyAdd(ans, singles[p]);
	}
	RevStr(b);
	return ans;
}
std::string MyMinus(std::string a, std::string b) {
	if (a == b) return "0";
	if (b[0] == '-') {
		std::string str = b.substr(1, b.size() - 1);
		return MyAdd(a, str);
	}
	if (a[0] == '-') {
		std::string str = a.substr(1, a.size() - 1);
		std::string ans = "-" + MyAdd(str, b);
		return ans;
	}
	if (!StrRefToNumGreater(a, b)) {
		return "-" + MyMinus(b, a);
	}
	std::string ans = "";
	RevStr(a);
	RevStr(b);
	int s = a.size();
	int subtract = 0;
	for (int i = 0; i < s; i++) {
		if (i < b.size()) {
			int k = a[i] - b[i] - subtract;
			subtract = 0;
			if (k < 0) {
				subtract = 1;
				k += 10;
			}
			ans.push_back((char)(k + '0'));
		}
		else {
			int k = a[i] - subtract - '0';
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
	RevStr(a);
	RevStr(b);
	RevStr(ans);
	return ans;
}
std::string MyDivide(std::string a, std::string b) {
	std::string ans = "0", c = a;
	while (StrRefToNumGreater(c, "0")) {
		c = MyMinus(c, b);
		ans = MyAdd(ans, "1");
	}
	if (StrRefToNumGreater("0", c)) {
		ans = MyMinus(ans, "1");
	}
	return ans;
}
std::string MyMod(std::string a, std::string b) {
	std::string c=a;
	while (StrRefToNumGreater(c, "0")) {
		c = MyMinus(c, b);
	}
	if (c == "0") return c;
	return MyAdd(c, b);
}
std::string MyPow(std::string x, std::string n) {
	if (StrRefToNumGreater("0",n)) return "0";
	if (n == "0") return "1";
	std::string k = MyPow(x, MyDivide(n, "2"));
	return ((MyMod(n, "2") != "0") ? MyMultiply(MyMultiply(x, k), k) : MyMultiply(k, k));
}
std::string MySqrt(std::string x) {
	if (x[0] == '-') return "-1";
	std::string s = "0";
	for (; !StrRefToNumGreater(s, x); s = MyAdd(s, "1")) {
		std::string pow = MyPow(s, "2"), pow1 = MyPow(MyAdd(s, "1"), "2");
		if (x == pow || (StrRefToNumGreater(x, pow) && StrRefToNumGreater(pow1, x))) {
			return s;
		}
	}
	return "0";
}

#pragma warning(default:4267)

#endif//MYSTRINGALGORITHM_HPP
