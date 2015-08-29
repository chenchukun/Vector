#include "Vector.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	Vector<int> x;
	x.push_back(12);
	x.push_back(33);
	x.push_back(4);
	x.push_back(1);
	x.traverse();
	cout << x.size() << endl;
	x.insert(0, 45);
	x.traverse();
	cout << x.size() << endl;
	x.insert(3, 5);
	x.traverse();
	cout << x.size() << endl;
	x.remove(3);
	x.traverse();
	cout << x.size() << endl;
	x.insert(5, 90);
	x.traverse();
	cout << x.size() << endl;
	x.remove(1,3);
	x.traverse();
	cout << x.size() << endl;
	cout << x.find(4) << endl;
	x.sort(0, 3);
	x.traverse();
	cout << "........................" << endl;
	Vector<int> t(x.begin(), x.end());
	t.traverse();
	t.push_back(0);
	t.insert(3, 7);
	t.traverse();
	t.sort();
	t.traverse();
	cout << t.search(4) << endl;
	cout << t.disordered() << endl;
	t.push_back(1);
	t.push_back(4);
	t.push_back(7);
	t.push_back(1);
	t.push_back(7);
	t.traverse();
	cout << t.disordered() << endl;
	Vector<int> y(t);
	t.sort();
	t.traverse();
	cout << t.disordered() << endl;
	t.uniquify();
	t.traverse();
	cout << t.disordered() << endl;
	y.traverse();
	y.deduplicate();
	y.traverse();
	cout << y.empty() << endl;
	y.reverse();
	y.traverse();
	cout << "........................" << endl;
	Vector<int> z = {2,3,4,5,4,1};
	z.traverse();

	Vector<int> zz(10,2);
	zz.traverse();
	cout << "........................" << endl;
	cout << "x: ";
	x.traverse();
	cout << "y: ";
	y.traverse();
	cout << "x == y:  " << (x == y) << endl;
	cout << "x > y:  " << (x > y) << endl;
	cout << "x >= y:  " << (x >= y) << endl;
	cout << "x <= y:  " << (x <= y) << endl;
	cout << "x < y:  " << (x < y) << endl;
	Vector<int> tt(x);
	cout << "tt: ";
	tt.traverse();
	cout << "x == tt:  " << (x == tt) << endl;
	tt.clear();
	tt.traverse();

	return 0;
}
