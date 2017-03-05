# include<Windows.h>
# include <iostream>
# include<string>
# include<vector>
# include<array>
# include<fstream>
# include<sstream>
# include<cstdlib>
# include<ctime>
# include<valarray>
# include<cctype>
# include<memory>
# include<list>
# include<queue>
# include<stack>
# include<set>
# include<iterator>
# include<algorithm>
# include<map>
# include<forward_list>
# include<functional>
# include "coordin.h"
# include"test.h"
namespace mychar2
{
	//char cc;
	void showchar2()
		;
}

//extern int cats, dogs,fleas;
using namespace mychar2;
using namespace std;
const double *f1(const double *ar, int n)
{
	return ar;
}
const double *f2(const double ar[], int n)
{
	return ar + 1;
}
const double *f3(const double *ar, int n)
{
	return ar + 2;
}
void print(const char *str, int width)
{
	for (int i=0; i < width&&str[i]; i++)
		std::cout << str[i];
}
void print(double d, int width)
{
	std::cout << "pint2\n";
}
void print(char *str)
{
	std::cout << "print char\n";
}
void print(char &c)
{
	std::cout << "&char\n";
}
void print(char c)
{
	std::cout << "char\n";
}
void print(const char *str)
{
	std::cout << "print const char\n";
}
template <typename T>
void swap1(T &a, T&b)
{
	T temp;
	temp = b;
	b = a;
	a = temp;
	
}
template < class T >
void swap1(T a[], T b[],int n)
{
	T temp;
	for (int i = 0; i < n; i++)
	{
		temp = a[i];
		a[i] = b[i];
b[i] = temp;
	}
}
void show(int a[])
{
	std::cout << a[0] << a[1] << '/';
	std::cout << a[2] << a[3] << '/';
	for (int i = 4; i < 8; i++)
		std::cout << a[i];
	std::cout << std::endl;
}
template<class T>
T lesser(T a, T b)
{
	return a < b ? a : b;
}
int lesser(int a, int b)
{
	a = (a < 0) ? -a : a;
	b = (b < 0) ? -b : b;
	return a < b ? a : b;
}
template <class T1, class T2>
void add(T1 a, T2 b)
{
	decltype(a + b) xpy = a + b;
	std::cout << a << "+" << b << ",xpy=" << xpy << std::endl;
}
auto h(int x, float y)->double
{
	return x + y;
}
/*void show3()
{
using namespace std;
cout << "dogs=" << dogs << "cats=" << cats << "fleas=" << fleas << endl;
}
void other()
{
using namespace debts;
person per = { "john", "han" };
showPerson(per);
debt d[3];
for (int i = 0; i < 3; i++)
getDept(d[i]);
for (int i = 0; i < 3; i++)
showDept(d[i]);
std::cout << sumDept(d,3);
}*/
void callme1(String &rsb)
{
	cout << "string passed by reference " << rsb << endl;
}
void callme2(String sb)
{
	cout << "string passed by value " << sb << endl;
}
bool newCustomer(double x)
{
	return std::rand()*x / RAND_MAX < 1;
}
void setStudent(Student1 &s, int quizzes)
{
	cout << "输入学生姓名:";
	getline(cin, s);
	cout << "输入学生成绩:";
	for (int i = 0; i < quizzes; i++)
		cin >> s[i];
	while (cin.get() != '\n')
		;
}

int main(int argc,char *argv[])
{
	srand(time(0));
	ostream_iterator<int, char>i_out(cout, "  ");
	ostream_iterator<string, char>s_out(cout, "  ");
	UseLess ul(3);
	UseLess ul1 = 3;
//	UseLess ul2 = ul1;
	UseLess ul3 = string("9999");
	UseLess ul4 = "9999";
	using namespace std;
	vector<int>v9;
	vector<int>vv1{ 1, 3, 5, 7, 9 ,10};
	vector<int>vv2 = { 2, 4, 6, 8 };	
	ifstream file1("filename");//ok:direct initialization
	//ifstream file2 = "filename";//error:copy constructor is private
	fstream fin;
	ofstream fout;
	planet plt;
	ostringstream outstr;
	string hdisk;
	string lit = "It was a dark and stormy day, and "
		"the full moon glowed brilliantly.";
	istringstream instr(lit);
	while (instr >> hdisk)
	{
		cout << hdisk << endl;
	}
	cout << "what 's the name of you hard disk:";
	getline(cin, hdisk);
	cout << "what 's its capacity in GB?";
	int cap;
	cin >> cap;
	string result_s = outstr.str();
	outstr << "the hard disk " << hdisk << "  has a capacity of " << cap << " gigabytes.\n";
	cout << result_s;

	cout << "\n系统可能生成最多临时文件名的个数:" << TMP_MAX << ",每个临时文件名的最大字符数:" << L_tmpnam << endl;
	char pszname[L_tmpnam] = { '\0' };
	cout << "\nhere are names:\n";
	for (int i = 0; i < 10; i++)
	{
		tmpnam(pszname);
		cout << pszname << endl;
	}
	int f_ct = 0;
	cout << fixed << right;
	fin.open("binary.txt", ios_base::in | ios_base::out | ios_base::binary);
	if (!fin.is_open())
		cout << "\n the file binary.txt read failed\n";
	else
	{
		cout << "\nhere are the new contents of the binary.txt file:\n";
		while (fin.read((char*)&plt, sizeof(plt)))
		{
			f_ct++;
			cout << setw(20) << plt.name << setprecision(0) << setw(12) << plt.population << setprecision(2)
				<< setw(12) << plt.g << endl;
		}
	}
	fin.clear();
	char c1 = 1.57e27;
	char c2 = 459282821;
	cout << "\nc1:" << c1 << ",c2=" << c2 << endl;

	int ct_cg;
	cout << "input the record number you want to change:";
	cin >> ct_cg;
	if (ct_cg < 0 || ct_cg >= f_ct)
	{
		cout << "invalid number,there are only " << f_ct << " records \n";
		exit(EXIT_FAILURE);
	}
	streampos s_pos = sizeof plt*ct_cg;
	fin.seekg(s_pos);
	cout << "your selection the " << ct_cg << "record:\n";
	fin.read((char*)&plt, sizeof(plt));
	cout << setw(20) << plt.name << setprecision(0) << setw(12) << plt.population << setprecision(2)
		<< setw(12) << plt.g << endl;
	cin >> plt;

	fin.seekg(s_pos);
	fin.write((char*)&plt, sizeof(plt));

	cout << "\nhere are the new contents of the binary.txt file:\n";
	fin.seekg(0);
	while (fin.read((char*)&plt, sizeof(plt)))
	{
		f_ct++;
		cout << setw(20) << plt.name << setprecision(0) << setw(12) << plt.population << setprecision(2)
			<< setw(12) << plt.g << endl;
	}

	fin.close();
	fout.open("binary.txt", ios_base::app | ios_base::binary);
	if (!fout.is_open())
		cout << "\n the file binary open failed\n";
	cin >> plt;
	fout << plt;
	fout.close();
	char arr_test[30];
	int n_char = 0;
	char c_char;
	if (argc == 1)
		cerr << "usage:" << argv[0] << " filename" << endl;
	long l_count = 0;
	long l_total = 0;
	for (int i = 1; i < argc; i++)
	{
		l_count = 0;
		fin.open(argv[i]);
		if (!fin.is_open())
		{
			cout << "\ncan't not open " << argv[i] << endl;

		}
		while (fin.get(c_char))
		{
			cout << c_char;
			l_count++;
		}
		l_total += l_count;
		fin.close();
		cout << "\nthis is file :" << argv[i] << ",have " << l_count << " characters" << endl;
	}
	cout << l_total << " characters in all files\n";
	for_each(vv1.begin(), vv1.end(), [](int x){cout << x << " "; });
	cout << endl;
	for_each(vv2.begin(), vv2.end(), [](int x){cout << x << " "; });
	cout << endl;
	v9.resize(29);

	merge(vv1.begin(), vv1.end(), vv2.begin(), vv2.end(), v9.begin());

	deque<int>flist6{ 5,4,1, 5,1,2,3,4,5,6,4 ,4,4,4,7, 8, 9, 2,3,4, 7 };
	deque<int>d_que6{ 2,3,4};
	vector<int>copy6(30);
	move(flist6.begin(), flist6.end(), copy6.begin());
	for_each(copy6.begin(), copy6.end(), outs<int>);
	cout << "\n\nflist6:\n";
	for_each(flist6.begin(), flist6.end(), outs<int>);
	cout << "\n\ncopy_back:\n";
	copy_backward(flist6.begin(), flist6.end(), copy6.end());
	for_each(copy6.begin(), copy6.end(), outs<int>);
	cout << "\n\n";

	//copy(flist6.begin(), flist6.end(), copy6.begin());
	//for_each(copy6.begin(), copy6.end(), outs<int>);
	//cout << "\n\n";
	copy_n(flist6.begin(), 10, copy6.begin());
	for_each(copy6.begin(), copy6.end(), outs<int>);
	cout << "\n\n";

	auto d_iter = find_end(flist6.begin(), flist6.end(), d_que6.begin(), d_que6.end());
	for_each(d_iter,flist6.end(), outs<int>);
	cout << "\n\n";
	d_iter = search(flist6.begin(), flist6.end(), d_que6.begin(), d_que6.end());
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";
	d_iter = search(flist6.begin(), flist6.end(), d_que6.begin(), d_que6.end(), [](int a, int b){return a == b + 2; });
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";
	d_iter = search_n(flist6.begin(), flist6.end(),4,4);
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";
	auto mis = mismatch(flist6.begin(), flist6.end(), d_que6.begin());
	cout << "\nmathch:" << *mis.first << "," << *mis.second << endl;
	mis = mismatch(flist6.begin(), flist6.end(), d_que6.begin(), [](int a, int b){return a > b; });
	cout << "\na>b:" << *mis.first << "," << *mis.second << endl;
	bool equ_not=equal(flist6.begin(), flist6.end(), d_que6.begin(), [](int a, int b){return a > b; });
	cout << "\na>b:" <<boolalpha << equ_not << endl;
	//bool is_per = is_permutation(flist6.begin(), flist6.end(), d_que6.begin(),myless);
	//cout << "\nis_per:" << boolalpha << is_per << endl;
	int div2=count_if(flist6.begin(), flist6.end(), [](int x){return x % 2 == 0; });
	cout << "\ndiv2=" << div2 << endl;
	d_iter = adjacent_find(flist6.begin(), flist6.end());
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";
	d_iter = adjacent_find(flist6.begin(), flist6.end(), [](int x, int y){return x + 3 == y; });
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";

    d_iter = find_end(flist6.begin(), flist6.end(), d_que6.begin(), d_que6.end(),myless);
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";

	 d_iter = find_first_of(flist6.begin(), flist6.end(), d_que6.begin(), d_que6.end());
	for_each(d_iter, flist6.end(), outs<int>);
	cout << "\n\n";

	cout << "\nall of >3:" << any_of(flist6.begin(), flist6.end(), big3) << endl;
	auto f_list6 = find_if_not(flist6.begin(), flist6.end(), big3);
	cout << "\nfind :" << *f_list6 << endl;
	string test_5[]{"what", "can", "i", "do", "for", "you", "can", "nihao", "you","you","you"};
	string test_6[]{"what", "can", "do", "you", "can", "nihao", "you", "you","should","apple"};
	vector<string> vect5{ "aaa", "aaa","bbb",  "cccccccccc","ddddd", "ddddd", "eeeeee", "fff" };
	vector<string>vect6(22);
	list<string>list_5(test_5, test_5 + 6);
	list<string>list_6(vect5.begin(), vect5.end());
	list<string>list_7(vect5.begin(), vect5.end());
	forward_list<string>flist_5(vect5.begin(),end(vect5));
	forward_list<string>flist_7(vect5.begin(), vect5.end());
	multiset<string,rever_s>set_5(vect5.begin(), vect5.end());
	multiset<string>set_5a(test_5, end(test_5));
	multiset<string>set_5b(test_6, end(test_6));
	multiset<string>set_5c(test_6, test_6+3);
	vector<string>vec_5a(test_5, end(test_5));
	vector<string>vec_5b(test_6, end(test_6));
	vector<string>vec_5c;
	vec_5c.resize(vec_5a.size() + vec_5b.size()+1);
	multiset<string>set_5d(vect6.begin(), vect6.end());
	cout <<endl<< boolalpha << includes(set_5b.begin(), set_5b.end(), set_5c.begin(), set_5c.end()) << endl;
	cout << "\nseta:\n";

	for_each(set_5a.begin(), set_5a.end(), outs<string>);
	cout << "\nsetb:\n";
	for_each(set_5b.begin(), set_5b.end(), outs<string>);
	sort(vec_5a.begin(),vec_5a.end());
	sort(vec_5b.begin(), vec_5b.end());
	
	auto set_p=set_union(vec_5a.begin(),vec_5a.end(),vec_5b.begin(),vec_5b.end(),vec_5c.begin());
	cout << "\nsetunion:\n";
	for_each(vec_5c.begin(), vec_5c.end(), outs<string>);
	set_p=set_intersection(vec_5a.begin(), vec_5a.end(), vec_5b.begin(), vec_5b.end(), vec_5c.begin());
	cout << "\nset_intersection:\n";
	for_each(vec_5c.begin(), set_p, outs<string>);
	set_p=set_difference(vec_5a.begin(), vec_5a.end(), vec_5b.begin(), vec_5b.end(), vec_5c.begin());
	cout << "\nset_set_difference:\n";
	for_each(vec_5c.begin(), set_p, outs<string>);
	set_p=set_symmetric_difference(vec_5a.begin(), vec_5a.end(), vec_5b.begin(), vec_5b.end(), vec_5c.begin());
	cout << "\nset_symmetric_difference:\n";
	for_each(vec_5c.begin(), set_p, outs<string>);

	cout << "\nsetc:\n";
	for_each(set_5c.begin(), set_5c.end(), outs<string>);

	cout << "\nset5:\n";
	for_each(set_5.begin(), set_5.end(), outs<string>);
	cout << "\n\n";
	auto insert1=set_5.insert("cbcc");
	
	for_each(insert1, set_5.end(), outs<string>);
	cout << "\n\n";
	//set_5.insert(set_5.begin(), "www");
	set_5.insert(test_5 + 2, test_5 + 5);
	for_each(set_5.begin(), set_5.end(), outs<string>);
	cout << "\naaa:\n";
	set_5.erase("aaa");
	for_each(set_5.begin(), set_5.end(), outs<string>);
	cout << "\nflist5:\n";
	for_each(flist_5.begin(), flist_5.end(), outs<string>);
	cout << "\n\n";
	flist_5.insert_after(flist_5.begin(), "yyyy");
	for_each(flist_5.begin(), flist_5.end(), outs<string>);
	cout << "\n\n";
	flist_5.erase_after(++flist_5.begin());
	for_each(flist_5.begin(), flist_5.end(), outs<string>);
	cout << "\n\nflist5:\n";
	flist_5.splice_after(flist_5.begin(),flist_7);
	for_each(flist_5.begin(), flist_5.end(), outs<string>);
	cout << "\n\nflist7:\n";
	for_each(flist_7.begin(), flist_7.end(), outs<string>);
	cout << "\n\n";

	list_5.sort();
	list_7.sort();

	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";
	for_each(list_7.begin(), list_7.end(), outs<string>);
	cout << "\n\n";
	list_5.merge(list_7);
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";
	for_each(list_7.begin(), list_7.end(), outs<string>);
	cout << "\nreverse:\n";
	list_5.reverse();
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";

	list_5.splice(list_5.begin(), list_6,list_6.begin());
	list_5.splice(list_5.begin(), list_6, list_6.begin());
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";

	list_5.splice(list_5.begin(), list_6);
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";
	list_5.unique();
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";

	list_5.remove("aaa");
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";
	list_5.remove_if(re_move);
	for_each(list_5.begin(), list_5.end(), outs<string>);
	cout << "\n\n";

	vect5.insert(vect5.begin(), "ggg");
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	auto iter_i=vect5.insert(vect5.begin()+3, "ggg");
	for_each(iter_i, vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.insert(vect5.begin(), 5,"zeng");
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.insert(vect5.begin(),test_5+2,test_5+5);
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.resize(20,"null");
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.resize(5);
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.assign(test_5, test_5 + 6);
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	//vect5.assign(8,"yong");
	//for_each(vect5.begin(), vect5.end(), outs<string>);
	//cout << "\n\n";
	auto v_erase = vect5.erase(vect5.begin() + 3);
	for_each(v_erase, vect5.end(), outs<string>);
	cout << "\n\n";
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.erase(vect5.begin() + 1, vect5.begin() + 3);
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\nfront:"<<vect5.front()<<",back:"<<vect5.back()<<endl;
	//vect5.clear();
	vect5.push_back("push back");
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\n";
	vect5.pop_back();
	for_each(vect5.begin(), vect5.end(), outs<string>);
	cout << "\n\ncapacity:" << vect5.capacity() << ",size:" << vect5.size() << endl;
	vect5.reserve(50);
	cout << "\n\ncapacity:" << vect5.capacity() << ",size:" << vect5.size() << endl;

	list<string>list5a(vect5.begin(),vect5.end());
	list<string>list5b(list5a);
	vector<UseLess>vuse;
	cout << "\nsize:" << vuse.size() << ",capacity:" << vuse.capacity() << endl;
	/*vuse.push_back(UseLess(1));
	vuse.push_back(UseLess(2,'a'));
	cout << "\nsize:" << vuse.size() << ",capacity:" << vuse.capacity() << endl;

	vuse.emplace(vuse.end(),3);
	vuse.emplace(vuse.end(), UseLess(4, 'b'));
	cout << "\nsize:" << vuse.size() << ",capacity:" << vuse.capacity() << endl;

	vuse.emplace_back(5);
	vuse.emplace_back(6,'c');
	vuse.emplace_back( UseLess(7, 'd'));
	cout << "\nsize:" << vuse.size() << ",capacity:" << vuse.capacity() << endl;
	cout << "\n\n*********\n\n";
	for (auto v : vuse)
		v.showData();
	cout << "\n\n*********\n\n";*/
	for_each(list5b.begin(), list5b.end(), outs<string>);
	double c_tt = 1.21;
	int i_ctt = 14;
	string s_test = "Mr. string objects.";

	show_list(i_ctt, c_tt);
	show_list(i_ctt + i_ctt, '!', 7, s_test);
	cout << use_ff<double>(c_tt, dub) << endl;
	cout << use_ff<double>(c_tt,square) << endl;
	cout << use_ff<double>(c_tt, Fp(5.0)) << endl;
	cout << use_ff<double>(c_tt,Fq(5.0)) << endl;
	cout << use_ff<double>(c_tt, [](double x){return x*x; }) << endl;
	cout << use_ff<double>(c_tt, [](double x){return x + x / 2.0; }) << endl;

	cout << use_f( c_tt,dub)<< endl;
	cout << use_f(c_tt, square) << endl;
	cout << use_f(c_tt, Fp(5.0)) << endl;
	cout << use_f(c_tt, Fq(5.0)) << endl;
	cout << use_f(c_tt, [](double x){return x*x; });
	cout << use_f(c_tt, [](double x){return x + x / 2.0; });
	using fnd = function < double(double) > ;
	fnd ef1 = dub;
	fnd ef2 = square;
	fnd ef3 = Fp(10.0);
	fnd ef4 = Fq(10.0);
	fnd ef5 = [](double x){ return x*x; };
	fnd ef6 = [](double x){return x + x / 2.0; };
	cout << use_f(c_tt, ef1) << endl;
	cout << use_f(c_tt, ef2) << endl;
	cout << use_f(c_tt, ef3) << endl;
	cout << use_f(c_tt, ef4) << endl;
	cout << use_f(c_tt, ef5) << endl;
	cout << use_f(c_tt, ef6) << endl;
	vector<int>numbers(Size1);
	generate(numbers.begin(), numbers.end(), rand);
	int count3 = count_if(numbers.begin(), numbers.end(), ff3);
	int count13 = count_if(numbers.begin(), numbers.end(), ff13);
	cout << "\ncount of numbers divide by 3:" << count3;
	cout << "\ncount of numbers divide by 13:" << count13;
	numbers.resize(Size2);
	generate(numbers.begin(), numbers.end(), rand);
	count3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
	 count13 = count_if(numbers.begin(), numbers.end(), f_mod(13));
	cout << "\ncount of numbers divide by 3:" << count3;
	cout << "\ncount of numbers divide by 13:" << count13;
	numbers.resize(Size3);
	generate(numbers.begin(), numbers.end(), rand);
	auto mod_1 = [](int x){ return x % 3 == 0; };
	count3 = count_if(numbers.begin(), numbers.end(),mod_1);
	count13 = count_if(numbers.begin(), numbers.end(), [](int x){return x % 13 == 0; });
	cout << "\ncount of numbers divide by 3:" << count3;
	cout << "\ncount of numbers divide by 13:" << count13;
	count3=count13 = 0;
	for_each(numbers.begin(), numbers.end(), [&](int x){count13 += x % 13 == 0; count3 += x % 3 == 0; });
	cout << "\ncount of numbers divide by 3:" << count3;
	cout << "\ncount of numbers divide by 13:" << count13;
	//cout << "\nthe randrom numbers are:\n";
	//copy(numbers.begin(), numbers.end(), ostream_iterator<int, char>(cout, "  "));
	//Bingo bin(3);
	//bin.f('a');
	{
		UseLess one(10, 'x');
		UseLess two(10, 'x');

		UseLess three(20, 'o');
		UseLess four(one + two);
		UseLess five;
		five = one + two;
		one.showData();
		two.showData();
		three.showData();
		four.showData();
		five.showData();
		five = move(one);
		five.showData();
		one.showData();
	}
	//myThrow();

	string s_filename;
	cout << "\nenter name for new file:";
	cin >> s_filename;
	fout.open(s_filename, ios_base::out | ios_base::binary);
	int rand_t = rand();
	const char *str_t3 = s_filename.c_str();
	fout.write((char*)&rand_t, sizeof(rand_t)).write(str_t3,s_filename.size());
	fout.close();
	cout << "\nenter name for new file:";
	cin >> s_filename;

	fout.open(s_filename, ios::out | ios::app);
	if (fout.is_open())
		cout << "\nfile open success\n";
	fout << "for you eyes only!\n";
	cout << "\nenter your secret number:";
	float n_num;
	cin >> n_num;
	fout << "your secret numer is:" << n_num << endl;
	fout.close();
	fout.open("hao123.txt", ios::app );
	if (!fout.is_open())
		cout << "\nfile open failed\n";
	fout << "\nthis is app app\n"<<rand()<<endl;
	fout.close();
	fin.open(s_filename);
	while (fin.get(c_char))
		cout << c_char;
	fflush(stdin);
	char gross[11];
	char socre[11];
	cout << "\nenter you name:";
	cin.get(gross, 11);
	if (cin.peek() != '\n')
		cout << "\nsorry ,we only have enough room for " << gross << endl;
	cin.ignore(255, '\n');
	cout << "dear " << gross << ",enter your title:";
	cin.get(socre, 11);
	if (cin.peek() != '\n')
		cout << "\nwe are forced to truncate your title\n";
	cout << "\nname:" << gross << ",title:" << socre << endl;
	cout << "\ninput gross and socre:";
	cin.read(gross,5);
	cout << "\ngross:" << gross << endl;
	cout << "\n enter  a  string for getline() processing:\n";
	cin.getline(arr_test, 30, '\n');
	cout << "\nhere is your input:\n" << arr_test << endl;
	cin.get(c_char);
	cout << "\nthe next input character is:" << c_char << endl;
	if (n_char != '\n')
		cin.ignore(30, '\n');
	cout << "\nenter a string for get() processing:\n ";
	cin.get(arr_test, 30, '\n');
	cout << "\nhere is your input:\n" << arr_test << endl;
	cin.get(c_char);
	cout << "\nthe next input character is:" << c_char << endl;
	if (cin.fail())
		cout << "the stream is fail\n";
	cout << "\n input string1:\n";
	while (cin.get(c_char))
	{
		if (c_char != '#')
		cout << c_char;
		else
		{
			cin.putback(c_char);
			break;
		}
	}
	if (!cin.eof())
	{
		cin.get(c_char);
		cout << "\nthe next input character is:" << c_char << endl;
	}
	else
	{
		cout << "\nendf of file reached\n";
	}
	if (cin.fail())
		cout << "the cin is failed\n";
	while (cin.peek() != '#')
	{
		cin.get(c_char);
		cout << c_char;
	}
	cin.get(c_char);
	cout << "\nthe next input character is:" << c_char << endl;
	cout << "\n input string:\n";
	while ((n_char=cin.get())!=EOF)
	{
		cout << n_char<<"  ";
	}

	cout << "\n input string2:\n";
	cin.get(c_char);
	while (c_char != '\n')
	{
		cout << c_char;
		n_char++;
		cin.get(c_char);
		//cin >> c_char;
	}
	cout << "\nct=" << n_char << endl;
	int sum_t1 = 0, input_t1 = 0;
	string str_t1;
	cin.exceptions(ios_base::failbit);
	cout << "\nenter numbers:";
	try
	{
		while (cin >> input_t1)
		{
			sum_t1 += input_t1;
		}
	}
	catch (ios_base::failure &bf)
	{
		cout << "\n" << bf.what() << endl;
		cout << "o!the horror\n";
		if (cin.fail())
			cout << "the stream is fail\n";
		cin.clear();

	}
	cout << "\nlast input is:" << input_t1 << ",sum:" << sum_t1 << endl;
	cout << "\ninput string:";
	cin >> str_t1;
	cout << "\nstring is:" << str_t1 << endl;

	cout << "\ninput a num:";

	int f_num;
	cin >> f_num;
	cout << "\nnum is:" << f_num << endl;
	cout << right;
	cout << setw(6) << "N" << setw(14) << "square root" << setw(15) << "fourth root"<<endl;
	for (int i = 10; i <= 100; i += 10)
	{
		double root = sqrt(i);
		cout << setfill('.') << setw(6) << i <<setfill(' ')<< setw(14) <<fixed << setprecision(3) <<
			root << setw(15) << setprecision(4) << sqrt(root)<<endl;
	}
	cout.setf(ios_base::left, ios_base::adjustfield);
	cout.setf(ios_base::showpoint);
	cout.setf(ios_base::showpos);
	cout.precision(3);
	ios_base::fmtflags old = cout.setf(ios_base::scientific, ios_base::floatfield);
	showFloat();

	cout.setf(ios_base::adjustfield, ios_base::internal);

	showFloat();
	cout.setf(old, ios_base::floatfield);
	showFloat();
	cout << "\nno show point:\n";
	cout.unsetf(ios_base::showpoint);
	//cout.setf(0, ios_base::floatfield);
	//cout.unsetf(ios_base::floatfield);
	showFloat();

	cout.setf(ios_base::right, ios_base::adjustfield);
	showFloat();
	cout.setf(ios_base::fixed, ios_base::floatfield);
	showFloat();
	float price1 = 20.40;
	float price2 = 1.9 + 8.0 / 9.0;
	int temperature = 63;
	cout << "price1:" << price1 << endl;
	cout << "price2:" << price2 << endl;
	cout.setf(ios_base::showpoint);
	cout << "price1:" << price1 << endl;
	cout << "price2:" << price2 << endl;
	cout.setf(ios::showpos);
	cout << "temperatur:" << temperature << endl;
	cout << hex << temperature << endl;
	cout.setf(ios::showbase);
	cout.setf(ios::uppercase);
	cout << temperature;
	cout.setf(ios::boolalpha);
	cout << true;
	cout.precision(2);
	cout << "price1:" << price1 << endl;
	cout << "price2:" << price2 << endl;

	cout.fill('*');
	string staff[2] = { "waldo whipsnsde", "wilmarie wooper" };
	long bunus[2] = { 900, 1350 };
	for (int i = 0; i < 2; i++)
	{
		cout << staff[i] << ":$";
		cout.width(7);
		cout << bunus[i] << "\n";
	}
	int width = cout.width(30);
	cout << "default filed width=" << width<< "\n";
	cout.width(5);
	cout << "N" << ":";
	cout.width(8);
	cout << "N*N" << ":\n";
	for (long i = 1; i <= 100; i *= 10)
	{
		cout.width(5);
		cout << i << ':';
		cout.width(8);
		cout << i*i << ":\n";
	}
	int hdo = 13;
	cout << hdo <<"    "<< hdo*hdo << "decimal\n";
	cout << hex << hdo << "    " << hdo*hdo << "hexadecimal\n";
	cout << oct << hdo << "    " << hdo*hdo << "octal\n";
	dec(cout);
	cout <<hdo << "    " <<hdo*hdo << "decimal\n";

	cout << "12345678901234567890\n";
	char ch_c = 'K';
	int t_i = 273;
	cout << ch_c << ":\n";
	cout << t_i << ":\n";
	cout << -t_i << ":\n";
	double f_1 = 1.200;
	cout << f_1 << ":\n";
	cout << (f_1 + 1.0 / 9.0) << ":\n";
	double f_2 = 1.67E2;
	cout << "f2:" << f_2 << ":\n";
	f_2 += 1.0 / 9.0;
	cout << f_2 << ":\n";
	cout << (f_2*1.0e4) << ":\n";
	double f_3 = 2.3e-4;
	cout << "f3:" << f_3 << ":\n";
	cout << f_3 / 10 << ":\n";
	int v_num;
	string v_str;
	cout << "\ninput string:";
	cin >> v_str;
	fflush(stdin);
	cout << "\n\ninput a num:"<<endl<<flush;
	cin >> v_num;
	
	vector<int>vec2(v_num, 2);
	for (int i = 0; i < v_num; i++)
		cout << vec2[i] << "\t";
	cout << "\n";
	Review rev;
	vector<Review> vect3;
	//cout << endl;
	cout << "\nflush\n" << flush;
	//while (cin.get() != '\n')
	//continue;
	//fflush(stdin);
	fflush(stdin);

	while (fillView(rev))
	{
		vect3.push_back(rev);
	}
	int v_size = vect3.size();
	if (v_size > 0)
	{
		cout << "thank you! you are entered the following \n ";
		for (int i = 0; i < v_size; i++)
			showView(vect3[i]);
		cout << "\n\nshow iterator:\n";
		auto next = vect3.begin();
		for (; next != vect3.end(); next++)
			showView(*next);
		vector<Review>copy = vect3;
		cout << "sort by title:\n";
		sort(vect3.begin(), vect3.end());
		for_each(vect3.begin(), vect3.end(), showView);
		cout << "sort by rating:\n";
		sort(vect3.begin(), vect3.end(), worseThan);
		for_each(vect3.begin(), vect3.end(), showView);
		cout << "aftering shuffling:\n";
		random_shuffle(vect3.begin(), vect3.end());
		for_each(vect3.begin(), vect3.end(), showView);
		if (v_size >= 3)
		{
			vect3.erase(vect3.begin() + 1, vect3.begin() + 3);
			cout << "after erase the 2rd to 3rd:\n";
			for_each(vect3.begin(), vect3.end(), showView);
			vect3.insert(vect3.begin(), copy.begin(), copy.begin() + 1);
			cout << "after insertion:\n";
			for_each(vect3.begin(), vect3.end(), showView);
		}
		cout << "after swap oldlist with books:\n";
		vect3.swap(copy);
		for_each(vect3.begin(), vect3.end(), showView);
	}
	else
		cout << "these is no data input\n";

	long val = 560031841;
	cout.write((char*)&val, sizeof(long)) << endl;
	const char *state1 = "florida";
	const char *state2 = "kansas";
	const char*state3 = "euphoria";
	int char_len = strlen(state2);
	for (int i = 0; i < char_len; i++)
	{
		cout.write(state2, i + 1);
		cout << endl;
	}
	for (int i = char_len; i > 0; i--)
	{
		cout.write(state2, i);
		cout << endl;
	}
	cout << "\nlen exceeding:\n";
	cout.write(state2, char_len + 5) << endl;
	int eggs = 12;
	cout.put('n').put('i').put(69);
	cout << 'w';
	char *amout = "mout";
	cout << &eggs << endl;
	cout << amout << endl;
	cout << (void*)amout << endl;
	cout << "\nlist 1:sum=" << sum({ 2, 3, 4 });
	initializer_list<double> d1 = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	cout << "\nlist 2:sum=" << sum(d1) << ",avg=" << avg(d1) << endl;
	d1 = { 16.0, 25.0, 36.0, 40.0, 64.0 };
	cout << "\nlist 3:sum=" << sum(d1) << ",avg=" << avg(d1) << endl;
	valarray<int>val_5(12);
	for (int i = 0; i < 12; i++)
		val_5[i] = rand() % 10;
	cout << "\noriginal array:\n";
	showVal(val_5, 3);
	cout << "\nsecond column:\n";
	showVal(val_5[slice(1, 4, 3)], 1);
	cout << "\nsecond row:\n";
	showVal(val_5[slice(3, 3, 1)], 3);
	cout << "\nset last column to 10:\n";
	val_5[slice(2, 4, 3)] = 10;
	showVal(val_5, 3);
	cout << "\nset first to sum next two:\n";
	val_5[slice(0, 4, 3)] = valarray<int>(val_5[slice(1, 4, 3)]) + valarray<int>(val_5[slice(2, 4, 3)]);
	showVal(val_5, 3);
	vector<double>vect_4;
	double temp4;
	cout << "\nenter numbers(<=0 to quit):";
	while (cin >> temp4&&temp4>0)
	{
		vect_4.push_back(temp4);
	}
	valarray<double>val_t4(vect_4.size());
	for (int i = 0; i < vect_4.size(); i++)
		val_t4[i] = vect_4[i];
	valarray<double>val_t5(val_t4);
	valarray<double>val_temp(vect_4.size());
	val_temp = val_t4 + val_t5;
	cout << "\tval_t4+val_t5:\n";
	for_each(begin(val_temp), end(val_temp), outs<double>);
	cout << "\n";

	val_temp = val_t4 * val_t5;
	cout << "\tval_t4*val_t5:\n";
	for_each(begin(val_temp), end(val_temp), outs<double>);
	cout << "\n";
	val_temp = 10.0*((val_t4 + val_t5)/2.0+val_t4*cos(val_t5));
	cout << "\tval_t4  val_t5:\n";
	for_each(begin(val_temp), end(val_temp), outs<double>);
	cout << "\n";

	valarray<double>sqt(vect_4.size());
	sqt = sqrt(val_t4);
	valarray<double>result_1(sqt.size());
	result_1 = val_t4 + 2.0*sqt;
	cout << "\nval_t4:\n";
	for_each(begin(val_t4), end(val_t4), outs<double>);
	cout << "\n";
	for (int i = 0; i < result_1.size(); i++)
		cout << sqt[i] << ":    " << result_1[i] << endl;
	vector<string>vect_3;
	string aaaaa("HELLO");
	cout << ToLower(aaaaa);
	cout << "\nenter words(enter quit to quit):";
	string vec_s1;
	while (cin >> vec_s1&&vec_s1 != "quit")
		vect_3.push_back(vec_s1);
	cout << "\nyou enter the following words:\n";
	for_each(vect_3.begin(), vect_3.end(), outs<string>);
	set<string>set_t3;
	//list<string>list_t3();
	//copy(vect_3.begin(), vect_3.end(), set_t3.begin());
	//copy(vect_3.begin(), vect_3.end(),insert_iterator<set<string>>(set_t3, set_t3.begin()));
	transform(vect_3.begin(), vect_3.end(), insert_iterator<set<string>>(set_t3, set_t3.begin()),ToLower);
	cout << "\nalphabetic list of words:\n";
	for_each(set_t3.begin(), set_t3.end(), outs<string>);
	map<string, int> map_t3;
	for (auto iter = set_t3.begin(); iter != set_t3.end(); iter++)
	{
		map_t3[*iter] = count(vect_3.begin(), vect_3.end(), *iter);
		//map_t3.insert(pair<string,int>(*iter,count(vect_3.begin(),vect_3.end(),*iter)));
	}
	cout << "\nword frequency:\n";
	for (auto iter = map_t3.begin(); iter != map_t3.end(); iter++)
		cout << (*iter).first << ":  " << (*iter).second << endl;
	array<int, 10>arr_t3 = { 4, 5, 4, 2, 2, 3, 4, 8, 1, 4 };
	list<int>li_a(arr_t3.begin(), arr_t3 .end());
	list<int>li_b(li_a);
	cout << "\noriginal list:\n";
	copy(li_a.begin(), li_a.end(), i_out);
	cout << "\nafter using remove method:\n";
	li_a.remove(4);
	copy(begin(li_a), end(li_a), i_out);
	cout << "\nafter using remove function:\n";
	list<int>::iterator last = remove(li_b.begin(), li_b.end(), 4);
	copy(li_b.begin(), li_b.end(), i_out);
	cout << "\nafter using erase:\n";
	li_b.erase(last, li_b.end());
	copy(li_b.begin(), li_b.end(), i_out);
	valarray<int>val_t{ 10, 11, 11, 11, 12, 13, 17, 16, 15, 14, 18 };
	cout << "\noriginal valarry:\n";
	for_each(&val_t[0], &val_t[11], outs<int>);
	array<int,11>arr_t2;
	copy(begin(val_t), end(val_t), arr_t2.begin());
	cout << "\ncopy to array:\n";
	for_each(arr_t2.begin(), arr_t2.end(), outs<int>);
	replace(begin(val_t), end(val_t), 11, 12);
	cout << "\nvalarry replace 11 to 12:\n";
	for_each(begin(val_t), end(val_t), outs<int>);
	vector<int>vect_t2(11);
	cout << "\n array replace and copy 11 to 12 to vector:\n";
	replace_copy(arr_t2.begin(), arr_t2.end(), vect_t2.begin(), 11, 12);
	for_each(arr_t2.begin(), arr_t2.end(), outs<int>);
	cout << "\nnow vector is:\n";
	for_each(begin(vect_t2), end(vect_t2), outs<int>);
	string permutation;
	cout << "\nenter the letter group (quit to quit)";
	while (cin >> permutation&&permutation != "quit")
	{
		cout << "\npermutation:\n";
		sort(permutation.begin(), permutation.end());
		cout << permutation << endl;
		while (next_permutation(permutation.begin(), permutation.end()))
			cout << permutation << endl;
		cout << "\nenter the letter group (quit to quit)";
	}
	array<double, 6> arr_1={ 28, 29, 30, 35, 38, 59 };
	array<double, 6>arr_2={ 63, 65, 69, 75, 80, 99 };
	deque<double>gr8(arr_1.begin(), arr_1.end());
	deque<double>m8(arr_2.begin(), arr_2.end());
	deque<double>sum_d(6);
	cout << "\ngr8:\n";
	for_each(gr8.begin(), gr8.end(), outs<double>);
	cout << "\nm8:\n";
	for_each(m8.begin(), m8.end(), outs<double>);
	transform(gr8.begin(), gr8.end(), m8.begin(), sum_d.begin(), plus<double>());
	cout << "\nsum:\n";
	for_each(sum_d.begin(), sum_d.end(), outs<double>);
	deque<double>prod(6);
	cout << "\ngr8*2.5\n";
	transform(gr8.begin(), gr8.end(), prod.begin(), bind1st(multiplies<double>(),2.5));
	for_each(prod.begin(), prod.end(), outs<double>);
	forward_list<int>flist1{ 50,100,90,180,60,210,415,88,188,201 };
	forward_list<int>flist2(flist1);
	TooBig<int> toob1(100);
	cout << "\noriginal flist1:\n";
	for_each(flist1.begin(), flist1.end(), outs<int>);
	cout << "\noriginal flist2:\n";
	for_each(flist2.begin(), flist2.end(), outs<int>);
	flist1.remove_if(toob1);
	flist2.remove_if(TooBig<int>(200));
	cout << "\nflist1>100:\n";
	copy(flist1.begin(), flist1.end(), ostream_iterator<int, char>(cout, "  "));
	cout << "\nflist2>200:\n";
	copy(flist2.begin(), flist2.end(), ostream_iterator<int, char>(cout, "   "));
	typedef pair<int, string> Pairs;
	typedef multimap<int, string> Map;
	map<int, string> map2 = { Pairs(415, "san rafael"), Pairs(415, "san francisco"), Pairs(510, "oakland"), Pairs(718, "brooklyn"), Pairs(718, "staten island"), Pairs(510, "berkeley") };
	Map map1 = { Pairs(415, "san francisco"), Pairs(510, "oakland"), Pairs(718, "brooklyn") };
	map1.insert(Pairs(718, "staten island"));
	map1.insert(Pairs(415, "san rafael"));
	map1.insert(Pairs(510, "berkeley"));
	cout << "\n415:   " << map1.count(415) << endl;
	cout << "510:   " << map1.count(510) << endl;
	cout << "718:   " << map1.count(718) << endl;
	cout << "\nmap:\n";
	for (auto map : map2)
		cout << "code:" << map.first << "  city:" << map.second << endl;
	cout << "\nmultimap:\n";
	for (auto map : map1)
		cout << "code:" << map.first << "   city:" << map.second << endl;
	cout << "\ncityies with 718:\n";
	pair<multimap<int,string>::iterator,multimap<int,string>::iterator> range = map1.equal_range(718);
	for (auto it = range.first; it != range.second; it++)
		cout << (*it).second << endl;
	queue<int>q_word;
	forward_list<int>f_list;
	priority_queue<int>pri_q; 
	array<int, 5>arr_t={ 7, 2, 6, 4, 3 };
	string ar_s1[]={ "buffoon", "thinkers", "for", "heavy", "can", "for" };
	string ar_s2 []= { "metal", "any", "food", "elegant", "deliver", "for" };
	array<string, 6> ar_s3 = { "buffoon", "thinkers", "for", "heavy", "can", "for" };

	set<string>set1(ar_s1,ar_s1+6);
	set<string>set2(ar_s2, ar_s2 + 6);
	multiset<string>set3(ar_s3.begin(),ar_s3.end());
	cout << "\nset1:\n";
	for_each(set1.begin(), set1.end(), outs<string>);
	cout << "\nset2:\n";
	copy(set2.begin(), set2.end(), ostream_iterator<string, char>(cout, "  "));
	cout << "\nset3:\n";
	copy(set3.begin(), set3.end(), s_out);
	cout << "\nset1 union set2\n";
	set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), s_out);
	cout << "\nset1 intersection set2\n";
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), s_out);
	cout << "\nset1 difference set2\n";
	set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), s_out);
	cout << "\nset union set2 to set4:\n";
	set<string>set4;
	set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), insert_iterator<set<string>>(set4, set4.begin()));
	for_each(set4.begin(), set4.end(), outs<string>);
	set4.insert("grungy");
	cout <<"\nset4 after insertion:\n";
	copy(set4.begin(), set4.end(), s_out);
	cout << "\nshowing a range:\n";
	copy(set4.lower_bound("ghost"), set4.upper_bound("spook"), s_out);
	int rand_time = rand() % 15 + 4;
	for (int i = 0; i < rand_time; i++)
	{
		q_word.push(rand() % 100);
		f_list.push_front(rand() % 100);
	}
	cout << "\narray:\n";
	for_each(arr_t.begin(), arr_t.end(), outs<int>);
	cout << "\nqueue:\n";
	while(!q_word.empty())
	{
		cout << q_word.front() << "\t";
		q_word.pop();
	}
	cout <<"\nforward_list:\n";
	for_each(f_list.begin(), f_list.end(), outs<int>);
	deque<int>dq;
	stack<int>stack1;
	rand_time = rand() % 15 + 4;
	for (int i = 0; i < rand_time; i++)
	{
		dq.push_back(rand() % 100);
		pri_q.push(rand() % 100);
		stack1.push(rand() % 100);
	}
	cout << "\ndequeue:\n";
	deque<int>dq1(dq);
	int d_test[4]{4, 3, 2, 1};
	copy(d_test, d_test + 4, front_insert_iterator<deque<int> >(dq1));//不能用于vector
	while (!dq.empty())
	{
		cout << dq.front() << "\t";
		dq.pop_front();
	}
	cout << "\npriority_queue:\n";
	while (!pri_q.empty())
	{
		cout << pri_q.top() << "\t";
		pri_q.pop();
	}
	cout << "\nstack:\n";
	while (!stack1.empty())
	{
		cout << stack1.top() << "\t";
		stack1.pop();
	}

	cout << "\ndq1 front insert:\n";
	for_each(dq1.begin(), dq1.end(), outs<int>);
	sort(dq1.begin(), dq1.end());
	cout << "\nsort deque:\n";
	for_each(dq1.begin(), dq1.end(), outs<int>);
	int dq_size = dq1.size();
	for (int i = 0; i < dq_size;i++)
	{
		cout << "\nerase front:\n";
		dq1.erase(dq1.begin());
		for_each(dq1.begin(), dq1.end(), outs<int>);
	}
	list<int>l_one(5, 2);
	int stuff[5]{1, 2, 4, 8, 6};
	list<int>l_two;
	l_two.insert(l_two.begin(), stuff, stuff + 5);
	int more[6] = { 6, 4, 2, 4, 6, 5 };
	list<int>l_three(l_two);
	l_three.insert(l_three.end(), more, more + 6);
	cout << "\nlist one:\n";
	for_each(l_one.begin(), l_one.end(), outs<int>);
	cout << "\nlist two:\n";
	for_each(l_two.begin(), l_two.end(), outs<int>);
	cout << "\nlist three:\n";
	for_each(l_three.begin(), l_three.end(), outs<int>);
	cout << "\nthree remove 2:\n";
	l_three.remove(2);
	for_each(l_three.begin(), l_three.end(), outs<int>);
	cout << "\nlist after splice one:\n";
	l_three.splice(l_three.begin(), l_one);
	for_each(l_three.begin(), l_three.end(), outs<int>);
	cout << "\nnow list 1:\n";
	for_each(l_one.begin(), l_one.end(), outs<int>);
	cout << "\nunique list 3:\n";
	l_three.unique();
	for_each(l_three.begin(), l_three.end(), outs<int>);
	cout << "\nsort &unique list 3:\n";
	l_three.sort();
	l_three.unique();
	for_each(l_three.begin(), l_three.end(), outs<int>);
	cout << "\nmerge two:\n"; 
	l_two.sort();
	l_three.merge(l_two);
	for_each(l_three.begin(), l_three.end(), outs<int>);
	string s1[4] = { "fine", "fish", "fashion", "fate" };
	string s2[2] = { "busy", "bats" };
	string s3[2] = { "silly", "singers" };
	vector <string>word(4);
	list<string>one_l(5,"zeng");
	list<string>two_l;
	two_l.insert(two_l.begin(), s1, s1 + 4);
	list<string>three_l(two_l);
	cout << "\nlist one:\n";
	for_each(one_l.begin(), one_l.end(), output);
	cout << "\nlist two:\n";
	for_each(two_l.begin(), two_l.end(), output);
	cout << "\nlist three:\n";
	for_each(three_l.begin(), three_l.end(), output);
	cout << "\nfront_insert:\n";
	copy(s3, s3 + 2, front_insert_iterator<list<string> >(three_l));//不能用于vector
	for_each(three_l.begin(), three_l.end(), output);

	copy(s1, s1 + 4, word.begin());
	cout << "\ns1:\n";
	for_each(word.begin(), word.end(), output);
	cout << "\nback_insert s2:\n";
	copy(s2, s2 + 2, back_insert_iterator<vector<string> >(word));
	for_each(word.begin(), word.end(), output);
	cout << "\ninsert front\n";
	copy(s3, s3 + 2, insert_iterator<vector<string>>(word, word.begin()));
	for_each(word.begin(), word.end(), output);
	int casts[10] = { 6, 7, 2, 9, 4, 11, 8, 7, 10, 5 };
	vector<int>dice(10);
	vector<int>dice_copy(10);
	copy(casts, casts + 10, dice.begin());
	cout << "\nenter the copy dice:" << endl;
	copy(istream_iterator<int, char>(cin), istream_iterator<int, char>(), dice_copy.begin());
	cin.clear();
	//while (cin.get() != '\n')
	//	continue;
	for (auto copy : dice_copy)
		cout << copy << "\t";
	ostream_iterator<int, char>o_out(cout, "  ");
	cout << "\n\nlet the dice be cast:\n";
	copy(dice.begin(), dice.end(), o_out);
	cout <<"\n\nimplicit reverse iterator:\n";
	copy(dice.rbegin(), dice.rend(), o_out);
	cout << "\n\nexplicit reverse iterator:\n";
	vector<int>::reverse_iterator rever;
	for (rever = dice.rbegin(); rever != dice.rend(); rever++)
		cout << *rever << "\t";
	cout << "\n\nno name ostream_iterator:\n";
	copy(dice.rbegin(), dice.rend(), ostream_iterator<int, char>(cout, "  "));
	sort(casts, casts + 10);
	cout << "\n\nsort array:\n";
	for (int cast : casts)
		cout << cast << "\t";
	cout << "\n\n";

	vector<double>scores_v(10);
	vector<double>::iterator iter;
	iter = scores_v.begin();
	for (int i = 0; iter != scores_v.end(); i++, iter++)
	{
		*iter = i + 1;
	}
	for (iter = scores_v.begin(); iter != scores_v.end(); iter++)
		cout << *iter << "\t";
	cout << "\n\n增强for循环:\n\n";
	for (double t : scores_v)
		cout << t << "\t";

	vector<int>rating(5);
	vector<string>title(5);
	cout << "endl" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "input title#" << i + 1;
		getline(cin, title[i]);
		cout << "input rating:";
		cin >> rating[i];
		cin.get();
	}
	for (int i = 0; i < 5; i++)
	{
		cout << "rating:" << rating[i] << ",title:" << title[i] << endl;
	}

	unique_ptr<string> ps; 
	unique_ptr<string> ps1(demo("convert"));
	//shared_ptr<string>spp(ps1);

	shared_ptr<string>spp1(demo("convert"));
	double *db5 = new double[5]{1, 2, 3, 4, 5};
	unique_ptr<double[]>pda(new double[5]{1, 2, 3, 4, 5});
	for (int i = 0; i < 5; i++)
		cout << pda[i]<< "\t";
	//auto_ptr<double[]>at(new double[5]{1, 2, 3, 4, 5});
	//shared_ptr<double[]>sha(new double[5]);
	//for (int i = 0; i < 5; i++)
		//cout << sha[i] << "\t";

	ps = demo("hello");
	cout << *ps << endl;
	Report rep3("hello");
	rep3 = report();
	unique_ptr<string>p1(new string("auto"));
	unique_ptr<string>p2;
	p2 = move(p1);
	//cout << *p2 << endl << *p1 << endl;
	shared_ptr<string>films[5] =
	{
		shared_ptr<string>(new string("fowl balls")),
		shared_ptr<string>(new string("duck walks")),
		shared_ptr<string>(new string("chicken runs")),
		shared_ptr<string>(new string("turkey errors")),
		shared_ptr<string>(new string("goose eggs"))
	};
	shared_ptr<string> pwin;
	pwin = films[2];
	for (int i = 0; i < 5; i++)
		cout << *films[i]<<endl;
	auto_ptr<double>ap(new double);
	{
		auto_ptr<Report>rep(new Report("hello world"));
		rep->commment();
	}
	{
		shared_ptr<Report>shp(new Report("share ptr"));
		shp->commment();
	}
	{
		unique_ptr<Report>unp(new Report("unique_ptr"));
		unp->commment();
	}
	string empty;
	string smalls= "bit";
	string larger = "elephants are a gril's best friend";
	cout << "empty:" << empty.size() <<","<<empty.capacity()<<endl;
	cout << "smalls:" << smalls.size() << "," << smalls.length()<<","<<smalls.capacity() << endl;
	cout << "larger:" << larger.size() << ","<<larger.capacity()<<endl;
	empty.reserve(50);
	cout << "empty:" << empty.capacity() << endl;
	string snake = "cobra";
	int where = snake.find_last_not_of("hark");
	cout << where << "、" << snake[where] << endl;
	char play;
	const int NUM1 = 26;
	cout << "will you play a word game?<y/n>:";
	cin >> play;
	play = tolower(play);
	const string wordlist[NUM1] = { "apiary", "beetle", "cereal",
		"danger", "ensign", "florid", "garage", "health", "insult",
		"jackal", "keeper", "loaner", "manage", "nonce", "onset",
		"plaid", "quilt", "remote", "stolid", "train", "useful",
		"valid", "whence", "xenon", "yearn", "zippy" };
	while (play == 'y')
	{
		string target = wordlist[rand() % NUM1];
		string errorChar;
		int length = target.length();
		string attempt(length, '-');

		cout << "guess my secret word..It has " << length << " letters,and you guess " <<
			"one letter at a time.you get " << length << " wrong guess.\n";
		cout << "your word:" << attempt << endl;
		int guess = 6;
		while (guess > 0 && attempt != target)
		{
			char g_char;
			cout << "guess a letter:";
			cin >> g_char;
			if (errorChar.find(g_char) != string::npos || attempt.find(g_char) != string::npos)
			{
				cout << "your already guess that,try again\n";
				continue;
			}
			int pos = target.find(g_char);
			if (pos == string::npos)
			{
				errorChar += g_char;
				cout << "bad guess!\n";
				guess--;
			}
			else
			{
				cout << "good guess\n";
				attempt[pos] = g_char;
				while (pos != string::npos)
				{
					pos = target.find(g_char, pos + 1);
					if (pos != string::npos)
						attempt[pos] = g_char;
				}
			}
			cout << "your word:" << attempt << endl;
			cout << "bad choices:" << errorChar << endl;
			cout << guess << " bad guesses left\n"; 
		}
		if (guess > 0)
			cout << "that's right\n";
		else		
			cout << "sorry ,that word is " << target << endl;
			cout << "will you play another?<y/n>";
			cin >> play;
			play = tolower(play);	
	}
	cout << "\n\n\nbye\n\n";
	cin.get();
	string line_s, fileName;
	fileName = "helloworld.txt";
	ifstream ifs;
	int line_count=0;
	ifs.open(fileName);
	if (ifs.is_open()==false)
		cout << "文件打开失败\n";
	else
	{
		getline(ifs, line_s, ':');
		while (ifs)
		{
			++line_count;
			cout << line_count << "、" << line_s << endl;
			getline(ifs, line_s, ':');
		}
	}
	char input3[60];
	cout << "input:";
	cin.get(input3,60);
	cout << input3 ;
	char test_ch;
	cout << "input char:";
	cin.get(test_ch);
	string one("zeng yong hua");
	cout << one << endl;
	string two(20, '$');
	cout << two << endl;
	string three(one);
	cout << three << endl;
	one += " is very good!\n";
	cout << one << endl;
	two = "soryy ,thaat was:";
	three[0] = 'p';
	string four;
	four = two + three;
	cout << four << endl;
	char alls[] = "all's well that end well,ha ha";
	string five(alls, 20);
	cout << five << endl;
	string six(alls + 6, alls + 10);
	cout << six << endl;
	string seven(&five[6], &five[10]);
	cout << seven << endl;
	string eight(four, 7, 16);
	cout << eight << endl;
	//cout << three << endl;
	struct dat
	{
		short a;
		short b;
	};
	long value = 0xA224B118;
	dat *pd = reinterpret_cast<dat *>(&value);
	cout << hex << pd->a << endl;
	cout << hex << pd->b << endl;

	int pop1 = 38383;
	const int pop2 = 2000;
	cout << "pop1,pop2:" << pop1 << "," << pop2 << endl;
	change(&pop1, -103);
	change(&pop2, -103);
	cout << "pop1,pop2:" << pop1 << "," << pop2 << endl;

	Grand *gr;
	Superb*su;
	Magnificent *high;
	Grand *low;
	const Magnificent *pbar;
	while (gr = getOne())
	{
		if (high = dynamic_cast<Magnificent*>(gr))
		{
			high->say();
			break;
		}
	}
    
	pbar = high;
	high->test = 1;
	Magnificent *pb;
	pb = const_cast<Magnificent*>(pbar);
	pb->test = 2;
	cout << pb->test << endl;
	//gr = const_cast<Grand*>(pbar);
	pb = (Magnificent*)(pbar);
	pb->test = 3;
	Magnificent *pb1 = static_cast<Magnificent*>(gr);
	Grand *pl = static_cast<Grand*>(pb1);
	//Stack* stack = static_cast<Stack*>(pb1);
	for (int i = 0; i < 10; i++)
	{
		gr = getOne();
		cout << "now is processing :" << typeid(*gr).name() << endl;
		gr->speak();
		if (su = dynamic_cast<Superb*>(gr))
			su->say();
		else
			cout << i<<": grand cant' convert\n";
		if (typeid(Magnificent) == typeid(*gr))
			cout << "yes ,you are really magnificent\n";
		try
		{
			Superb &rs = dynamic_cast<Superb&>(*gr);
		}
		catch (bad_cast &e)
		{
			cout<<e.what()<<endl;
		}
	}
	try
	{
	test();

	}
	catch (exception &e)
	{
		cout<<e.what();
	}
	{
		double vals1[12] =
		{
			1220, 1100, 1122, 2212, 1232, 2334,
			2884, 2393, 3302, 2922, 3002, 3544
		};

		double vals2[12] =
		{
			12, 11, 22, 21, 32, 34,
			28, 29, 33, 29, 32, 35
		};
		sales sa1(2011, vals1, 12);
		labelSales sa2("zeng",2012, vals2, 12);
		cout << "first try block:\n";
		try
		{
			int i;
			cout << "Year:" << sa1.Year() << endl;
			for (i = 0; i < 12; i++)
				cout << sa1[i] << "\t";
			cout << "\n\nYear:" << sa2.Year() << endl;
			cout << "Label:" << sa2.Lable() << endl;
			for (i = 0; i <= 12; i++)
				cout << sa2[i] << "\t";
		}

		catch ( labelSales::nbad_index &ls)
		{
			cout << ls.what();
			cout << "Label:" << ls.label_val()<<endl;
			cout << "Index:" << ls.Index()<<endl;
		}
		catch (sales::bad_index &bi)
		{
			cout << bi.what();
			cout << "Index:" << bi.Index() << endl;
		}
		cout << "next try block2\n";

		try
		{
			sa2[2] = 37.5;
			sa1[20] = 23345;
			cout << "end   of try block2\n";
		}
		catch (labelSales::nbad_index &ls)
		{
			cout << ls.what();
			cout << "Label:" << ls.label_val() << endl;
			cout << "Index:" << ls.Index() << endl;
		}
		catch (sales::bad_index &bi)
		{
			cout << bi.what();
			cout << "Index:" << bi.Index() << endl;
		}	
	}
	try
	{
		test();

	}

	catch (exception &e1)
	{
		cout << e1.what() << endl;
	}
	catch (myException &e)
	{
		cout<<e.what()<<endl;
	}
	double h_num1, h_num2, h_num3;
	{
		Demo d1(string("hello"));
		cout << "input two numbers:";

		while (cin >> h_num1 >> h_num2)
		{
			try
			{
				h_num3 = means(h_num1, h_num2);
				cout << h_num1 << "与" << h_num2 << "相运算的结果是:" << h_num3<<endl;
				cout << "input next pair" << endl;

			}
			catch (bad_hemen &bh)
			{
				bh.message();
				continue;
			}
			catch (bad_gemen &bg)
			{
				bg.MSG();
				break;
			}
			cout << "input two numbers:";
		}
		d1.show();
	}
	QueueTP<string> qtp;
	string qname;
	while (!qtp.isFull())
	{
		cout << "input you name to served:";

		getline(cin, qname);
		qtp.enQueue(qname);
	}
	while (!qtp.isEmpty())
	{
		cout << "now is processing:";
		qtp.deQueue(qname);
		cout << qname << endl;
	}
	testa ta;
	testb tb;
	testc tc;
	tc.showc();
	ta.showa(tb);
	TV s42;
	s42.settings();
	s42.onoff();
	s42.settings();
	s42.channelUp();
	s42.settings();
	Remote remo;
	remo.setChan(s42, 10);
	remo.volUp(s42);
	remo.volUp(s42);
	s42.settings();
	TV s58(TV::on);
	s58.set_mode();
	remo.setChan(s58, 28);
	s58.settings();
	OutputDebugString("debug begin\n");
	using mfint = ManyFriend < int > ;
	using mfd = ManyFriend <double> ;
	mfint hfi1(10);
	mfint hfi2(20);
	mfd hfdb(10.5);
	show2(hfi1, hfi2);
	show2(hfdb,hfi2);
	{
		count<int>();
		HasFriendT<int>hf1(10);
		count<int>();
		HasFriendT<int>hf2(20);
		count<int>();
		HasFriendT<double>hfdb(10.5);
		count<double>();
		report(hf1);
		report(hf2);
		report(hfdb);
	}
	int ni;
	double nb;
	Clob<Stack2> nebula;
	cout << "input ni,nb:";
	while (cin >> ni >> nb&&ni > 0 && nb > 0)
	{
		if (!nebula.push(ni, nb))
			break;
		cout << "input ni,nb:";
	}
	while (nebula.pop(ni, nb))
		cout<<ni<<"is pop,"<<nb<<"is pop\n";
	beta1<double>guy(3.5, 3);
	guy.show();
	cout << guy.blab(10, 2.3) << endl;
	cout << guy.blab(10.0, 2.3) << endl;
	Pair<string, int>ratings[4] = 
	{
		Pair<string,int>("the purpled duck",5),
		Pair<string, int>("jaquie's frisco al fresco",4),
		Pair<string, int>("Cafe Souffle",5),
		Pair<string, int>("Bertie's Eats ",3)
	};
	int joints = sizeof(ratings) / sizeof(Pair<string, int>);
	for (int i = 0; i < joints; i++)
		cout << "second:" << ratings[i].second() << ",first:" << ratings[i].first() << endl;
	ratings[3].first() = "Bertie's Fab Eats";
	ratings[3].second() = 6;
	cout << "second:" << ratings[3].first() << ",first:" << ratings[3].second() << endl;
	ArrayTP<int, 10>sum;
	ArrayTP<double, 10>average;
	ArrayTP<ArrayTP<int, 5>, 10>twodee;
	for (int i = 0; i < 10; i++)
	{
		sum[i] = 0;
		for (int j = 0; j < 5; j++)
		{
			twodee[i][j] = (i + 1)*(j + 1);
			sum[i] += twodee[i][j];
		}
		average[i] = sum[i] / 5;
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << twodee[i][j] << "\t";
		cout << " sum:" << sum[i] << ",average:" << average[i] << endl;
	}
	int stack_size;
	const int NUM = 10;
	cout << "please enter the stack size:";
	cin >> stack_size;
	const char *in[NUM] = {"1:hank gilgamesh","2: kiki ishtar","3 betty rocker","4 Ian Flagranti",
	"5 Wolfgang Kibble","6 portia koop","7 Joy Almondo","8 Xaverie Paprika","9 Juan Moore","10 Misha Mache"};
	const char *out[NUM];
	int processed = 0;
	int nextin = 0;
	const char *temp;
	Stack2<const char*> stack2(stack_size);
	srand(time(0));
	while (processed < NUM)
	{
		if (stack2.isEmpty())
			stack2.push(in[nextin++]);
		else
		{
			if (stack2.isFull())
				stack2.pop(out[processed++]);
			else
			{
				if (rand() % 2 && nextin < NUM)
					stack2.push(in[nextin++]);
				else
					stack2.pop(out[processed++]);
			}
		}
	}
	cout << "out:\n";
	for (int i = 0; i < NUM; i++)
		cout << out[i] << endl;

	Stack1<int> sta1;
	char char_choice;
	int num_stack;
	cout << "输入a进栈,p退栈,q退出:";
	while (cin >> char_choice&&std::tolower(char_choice) != 'q')
	{
		while (cin.get() != '\n')
			continue;
		if (!isalpha(char_choice))
		{
			cout << "输入字符";
			continue;

		}
		switch (char_choice)
		{
		case 'a':
		case 'A':
			cout << "input a number a add:";
			cin >> num_stack;
			if (sta1.push(num_stack))
			{
				cout << num_stack << "is push\n";
			}
			break;
		case 'p':
		case 'P':
			if (sta1.pop(num_stack))
				cout << num_stack << "is pop\n";
			break;
		}
		cout << "输入a进栈,p退栈,q退出:";
	}
	F ff;
	ff.q();
	//ff.omg();
	baseDMA base;
	thirdDMA third(base,"hello","world");
	waiter bob("bob apple", 314l, 5);
	singer bav("beverly hills", 512l, 3);

	worker *wo1=&bav;
	SingerWaiter sd(*wo1,10,6);
	worker *wo2 = (waiter*)&sd;

	//sd.waiter::show();
	sd.show();

	waiter w_temp;
	singer t_temp;
	worker *pw[4] = { &bob, &bav, &w_temp, &t_temp };
	for (int i = 2; i < 4; i++)
		pw[i]->set();
	for (int i = 0; i < 4; i++)
		pw[i]->show();
	const int pupils = 3;
	const int quizzes = 5;
	Student1 stu[pupils] = { Student1(quizzes), Student1(quizzes), Student1(quizzes) };
	int i;
	for (i = 0; i < pupils; i++)
		setStudent(stu[i], quizzes);
	for (i = 0; i < pupils; i++)
		cout<<stu[i].Name()<<endl;
	for (i = 0; i < pupils; i++)
	{
		cout << stu[i];
		cout<< ",average:" << stu[i].Average() << endl;
	}
	valarray<int> v2(10,8);
	for (int i = 0; i < v2.size(); i++)
		cout << v2[i]<<"\t";
	double gpa[5] = { 3.1, 3.5, 3.8, 2.9, 2.33 };
	valarray<double>v4 (gpa, 4);
	cout << "sum=" << v4.sum();
	for (int i = 0; i < v4.size(); i++)
		cout << "\t" << v4[i];
	{
		baseDMA shirt("portabellly", 8);
		lacksDMA ballon("red", "blimpo", 4);
		hasDMA map("mercator", "buffolo key", 5);
		cout << shirt;
		cout << ballon;
		cout<< map;
		lacksDMA ballon2(ballon);
		cout << ballon2;
		hasDMA map2;
		map2=map;
		cout << map2;
	}
	AcctABC *clients[4];
	string accname;
	long num;
	double balance;
	double rate;
	double oweMoney;
	double maxLoan;
	for (int i = 0; i < 4; i++)
	{
		cout << "输入账户姓名:";
		getline(cin, accname);
		cout << "输入账户账号:";
		cin >> num;
		cout << "输入余额:";
		cin >> balance;
		int choice;
		cout << "输入1创建BrassAccount、输入2创建BrassPlus:";
		while (!(cin>>choice)||choice!=2&&choice!=1)
			cout << "输入1创建BrassAccount、输入2创建BrassPlus:";
		if (1 == choice)
			clients[i] = new BrassAccount1(accname, num, balance);
		else
		{
			cout << "输入应还银行金额:";
			cin >> oweMoney;
			cout << "输入利率:";
			cin >> rate;
			cout << "输入最大贷款额度:";
			cin >> maxLoan;
			clients[i] = new BrassPlus1(accname, num, balance, oweMoney, rate, maxLoan);
		}
		while (cin.get() != '\n')
			;
	}
	for (int i = 0; i < 4; i++)
	{
		clients[i]->viewAct();
		delete clients[i];
	}
	BrassAccount piggy("porcelot pigg",381299, 4000.00);
	BrassPlus hoggy("horatio hogg", 382288, 3000.00);
	hoggy.show();
	hoggy.show();
	piggy.viewAct();
	hoggy.viewAct();

	cout << "virtual\n\n";
	BrassAccount &ba1 = piggy;
	BrassAccount &ba2 = hoggy;
	ba1.viewAct();
	ba2.viewAct();
	cout << "virtual2\n\n";

	BrassAccount *pa1 = new BrassAccount("porcelot pigg", 381299, 4000.00);
	BrassAccount *pa2 = new BrassPlus("horatio hogg", 382288, 3000.00);
	pa1->viewAct();
	pa2->viewAct();
	delete pa1;
	delete pa2;
	BrassPlus &ba3 = (BrassPlus)piggy;
	cout << "向下转换:\n";
	ba3.viewAct();
	ba3.withDraw(4200);
	hoggy.deposit(1000);
	cout << "\n\n存入1000后余额:" << hoggy.Balance() << endl;
	piggy.withDraw(4200);
	hoggy.withDraw(4200);
	hoggy.viewAct();
	RatedPlayer rp;
	rp.Name();
	TableTennisPlayer ttp1("chuck", "blizzard", true);
	TableTennisPlayer ttp2("tara", "booaba", false);
	ttp1.Name();
	if (ttp1.HasTable())
		cout << ":has a table\n";
	else
		cout << ":hasn't a table\n";
	ttp2.Name();
	if (ttp2.HasTable())
		cout << ":has a table\n";
	else
		cout << ":hasn't a table\n";
	RatedPlayer rp1(1140, "mallory", "duck", true);
	rp1.Name();
	if (rp1.HasTable())
		cout << ":has a table\n";
	else
		cout << ":hasn't a table\n";
	RatedPlayer rp2(1150, ttp1);
	rp2.Name();
	TableTennisPlayer &rt = rp1;
	TableTennisPlayer *pt = &rp1;

	rt.Name();
	pt->Name();
	cout << ",rate:" << rp2.Rating() << endl;
	TableTennisPlayer ttp3(rp2);
	ttp3.Name();
	ttp3 = rp1;
	ttp3.Name();

	//RatedPlayer &rr = ttp1;
	//RatedPlayer *pr = &ttp1;
	//rr.Name();
	//pr->Name();
	//cout<<rr.Rating()<<endl;
	std::srand(std::time(0));
	cout << "输入队列的大小:";
	int size;
	cin>> size;
	Queue qu(size);
	Queue qu1 ;
	//qu1 = qu;
	cout << "输入模拟时间:";
	int hours;
	cin >> hours;
	cout << "输入每小时顾客数:";
	int perhour;
	cin >> perhour;
	int cyclelimit = hours*60;
	int min_per_cur = 60 / perhour;
	int customers = 0;//
	int time_wait = 0;
	int line_wait = 0;
	int turnaways = 0;
	int served = 0;
	int sum_line = 0;
	Item1 item;
	for (int i = 0; i < cyclelimit; i++)
	{
		if (newCustomer(min_per_cur))
		{
			customers++;
			item.set(i);
			if(!qu.enQueue(item))
				turnaways++;
		}
		if (time_wait <= 0 && !qu.isEmpty())
		{
			qu.deQueue(item);
			time_wait = item.ptime();
			line_wait += i - item.when();
			served++;
		}
		if (time_wait > 0)
			time_wait--;
		sum_line += qu.queueCount();
	}
	if (customers)
	{
		cout << "接受的顾客人数:" << customers << endl;
		cout << "受服务的顾客人数:" << served << endl;
		cout << "被拒绝的人数:" << turnaways << endl;
		cout << "平均队列大小:" << sum_line / cyclelimit << endl;
		cout << "平均等待时间:" << line_wait / served << endl;
	}
	char *buffer = new char[512];
	Testing *pc1, *pc2;
	pc1 = new (buffer)Testing;
	pc2 = new Testing("heap1", 20);
	cout << (void*)buffer << endl <<pc1<<endl<< pc2 << endl;
	pc1->show();
	pc2->show();
	Testing *pc3, *pc4;
	pc3 = new (buffer+sizeof(Testing))Testing;
	pc4 = new Testing("heap2", 20);
	cout << (void*)buffer << endl << pc3 << endl << pc4 << endl;
	pc3->show();
	pc4->show();
	delete pc2;
	delete pc4;
	pc1->~Testing();
	pc3->~Testing();
	delete[]buffer;
	//delete pc1;
	//delete pc3;
	String name;
	cout << "hi,what 's your name:";
	cin >> name;
	String names[10];
	cout << name << ",please enter up to 10 short saying s <empty line to quit>:";
	int count = 0;
	for ( i = 0; i < 10; i++)
	{
		char temp[81];
		cout << i + 1 << ":";
		cin.get(temp, 81);
		while (cin&&cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')
			break;
		else
			names[i] = temp;
	}
	count = i;
	if (count> 0)
	{
		cout << "here are you sayings:\n";
		for (i = 0; i < count; i++)
			cout << names[i][0] << ":" << names[i];
		int shortest(0), first(0);
		for (i = 1; i <count; i++)
		{
			if (names[i].length() < names[shortest].length())
				shortest = i;
			if (names[i] < names[first])
				first = i;
		}
		cout << "shortest saying:\n" << names[shortest];
		cout << "first alphabetically:" << names[first];
		cout << "this program use " << String::HowMany() << "objects ,bye\n";
	}

	//using namespace std;
	{
		String headline1("hello");
		String headline2("world");
		String sports("i like sports");
		std::cout << headline1;
		std::cout << headline2;
		std::cout << sports;
		callme1(headline1);
		callme2(headline2);
		String sailor = sports;
		cout << sailor;
		String knot;
		knot = headline1;
		cout << knot;
		cout << "exit the block\n";
		cin >> knot;
		cout << knot;
	}
	/*{
		StringBad headline1("hello");
		StringBad headline2("world");
		StringBad sports("i like sports");
		std::cout << headline1;
		std::cout << headline2;
		std::cout << sports;
		callme1(headline1);
		callme2(headline2);
		StringBad sailor = sports;
		cout << sailor;
		StringBad knot;
		knot = headline1;
		cout << knot;
		cout << "exit the block\n";
	}*/
	cout << "end of main\n";
	Stonewt incognito = 275;
	incognito.show_lbs();
	incognito.show_pounds();
	Stonewt wolfe(285.7);
	Stonewt taft(21, 8);
	wolfe.show_lbs();
	wolfe.show_pounds();
	taft.show_lbs();
	taft.show_pounds();
	incognito = 276.8;
	incognito.show_lbs();
	incognito.show_pounds();

	taft = 325;
	taft.show_lbs();
	taft.show_pounds();
	double test = wolfe;
	int test2= wolfe;
	cout << "test=" << test << endl;
	//long test3 = wolfe;
	cout << "wolfe=" << int(wolfe) << endl;

	cout << "test2=" << test2 << endl;
	Stonewt total;
	//total = test +wolfe ;
	//cout << "total=" <<(double) total << endl;
	using VECTOR::Vector;
	srand(time(0));
	Vector step;
	Vector result(0.0, 0.0); 
	unsigned long steps = 0;
	cout << step << result;
	cout << "enter taget distance:";
	double target;
	while (cin >> target)
	{
		cout << "enter the length:";
		double length;
		if (!(cin >> length))
			break;
		while (result.magval()< target)
		{
			double direction = rand() % 360;
			step.reset(length, direction, Vector::ROL);
			result =result+ step;
			steps++;
		}
		cout << "after " << steps << "steps,the subject has following the location\n";
		cout << result;
		result.polor_mode();
		cout << "or\n" << result;
		cout << "the average step:" << result.magval() / steps;
		result.reset(0.0, 0.0);
		cout << "enter the distance:";
	}
	/*Time planning;
	Time coding(4, 35);
	Time fixing(2, 47);
	Time total,adjust;

	planning.showTime();
	coding.showTime();
	fixing.showTime();
	total = coding+fixing;
	//total = coding.sum(fixing);
	total.showTime();
	adjust = 1.5*total;
	adjust.showTime();
	cout << adjust<<coding;
	char ch;
	Stack stack;
	unsigned long num;
	cout << "input a to add,p to pop,q to quit:";
	while (cin >> ch&&ch != 'q')
	{
		while (cin.get() != '\n')
			continue;
		if (!isalpha(ch))
		{
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case 'a':
		case 'A':
			cout << "input a number to add:";
			cin >> num;
			stack.push(num);
			break;
		case 'p':
		case 'P':
			if(stack.pop(num))
			cout << "the" << num << "is pop";
			break;
		}
		cout << "input a to add,p to pop,q to quit:";
	}
	{
		Stock stock{ "hello" };
		stock.show();
		stock.accquire("张三", 20, 12.50);
		stock.show();
		stock.buy(15, 18.125);
		stock.show();
		stock.sell(400, 20.00);
		stock.show();
		stock.buy(300000, 40.125);
		stock.show();
		stock.sell(300000, 0.125);
		stock.show();
		cout << "\n\n\nlook here\n\n";
		Stock stock2 = Stock("boffo", 2, 2.0);
		stock2.show();
		stock2 = stock;
		stock.show();
		stock2.show();
		stock = Stock("hello kity", 10, 50.0);
		stock.show();
		cout << "the top total is";
		stock.topVal(stock2).show();
	}

	double *pd1, *pd2;
	char buffer[512];
	student stu;
	stu.name = "hello";
	stu.no = 1211;
	stu.showStu(); 
	stu.setName("张三");
	stu.showStu();
	cout << stu.getName() << endl;
	using debts::debt;
	using debts::showDept;
	debt deb = { { "hello", "world" }, 120.0 };
	showDept(deb);
	other();
	pd1 = new double[5];
	pd2 = new (buffer)double[5];
	for (int i = 0; i < 5; i++)
		pd2[i] = pd1[i] = 1000 + 20.0*i;
	for (int i = 0; i < 5; i++)
		cout << pd1[i] << " at " << &pd1[i] << " ; " << pd2[i] << " at " << &pd2[i] << endl;
	rect rplace;
	polar pplace;
	show1();
	show2();

	show3();

	/*cout << "enter two numbers:";
	while (cin >> rplace.x >> rplace.y)
	{
		pplace=rect_to_polar(rplace);
		show_polar(pplace);
		cout << "next two numbers:";
	}*/
/*
	cout << h(3, 4.1) << endl;
	int m = 20, n = -30;
	double x = 15.5, y = 25.9;
	char c;

	using namespace mychar;
	showchar();
	decltype (m)decl='c';
	decltype (c)decl2 = 'd';
	decltype(x + m)decl3;
	decl3 = x + m;
	add(m, n);
	add(m, x);
	add(m, decl2);
	cout << decl3 << endl;
	cout << decl << endl;
	cout << decl2 << endl;

	cout << lesser(m, n) << endl;
	cout << lesser(x, y) << endl;
	cout << lesser<>(m, n) << endl;
	char str1[20]="hello";
	int d1[]{0, 7, 0, 4, 1, 7, 7, 6};
	int d2[] = { 0, 7, 2, 0, 1, 9, 6, 9 };
	show(d1);
	show(d2);
	swap1(d1, d2, 8);
	show(d1);
	show(d2);

	int i = 10, j = 20;
	cout << "i=" << i << ",j=" << j << endl;
	swap1(i, j);
	cout << "now" << "i=" << i << ",j=" << j << endl;
	double i1 = 10.01, j1 = 20.01;
	cout << "i=" << i1 << ",j=" << j1 << endl;
	swap1(i1, j1);
	cout << "now" << "i=" << i1 << ",j=" << j1 << endl;
	string i2 = "hello", j2 = " world";
	cout << "i=" << i2 << ",j=" << j2 << endl;
	swap1(i2, j2);
	cout << "now" << "i=" << i2 << ",j=" << j2 << endl;
	//print(ch);
	print('c');
	print("hello");
	print(str1);
	print(7.0, 3);
	print(str1, strlen(str1));
	/*float tree = 3;
	int guess(3.9822);
	int dept = 7.2e12;
	const int  a = 4;
	char c1{ 123 };
	//char c2{ 31325 };
	char c3{ a};

	std::cout << "tree=" << tree<<std::endl;
	std::cout << "guress=" << guess<<std::endl;
	std::cout << "dept=" << dept << std::endl;

	system("echo nihao");
	//MessageBox(NULL, "nihao", "hello world", MB_OK);
	using namespace std;
	int auks, bats, coots;
	auks = 19.99 + 11.99;
	bats = (int)19.99 + (int)11.99;
	coots = int(19.99) + int(11.99);
	cout << "auks=" << auks << "bats=" << bats << "coots=" << coots << endl;
	auto n = 100;
	auto x = 1.5;
	auto y = 1.3e14l;
	auto c = 'c';
	cout << "n=" << n << "x=" << x << "y=" <<y<<"c="<< c << endl;
	short things[] = { 1, 3, 5, 7 };
	int num = sizeof things / sizeof(short);
	cout << "num=" << num << endl;
	cout << "hello";
	using namespace std;
	char name[20];
	cout << "enter your name:";
	//cin >> name;
	cin.get(name, 20).get();
	cout << name << endl << "enter your favourite dessert:";
	char dessert[20];
	//cin >> dessert;
	cin.get(dessert, 20);
	cout << "i have some " << dessert << "for you," << name << endl;

	string a{"what can i do for you"};
	string str2 = "hello";
	cout << a << ",the length is"<<a.size()<<","<<str2 << endl;
	string str1;
	char str3[20]="hello";
	str1 = "hello";
	int *n = new int;
	*n = 10001;
	cout << "n=" <<* n << endl;
	const char *p;
	char *t="nello" ;
	p=t;
	delete n;
	int *array = new int[10];
	delete []array;
	int *i, *j;
	int *a[10];
	//a[0] = j - i;

	class inflat
	{
	public:
	char name[20];
	float volume;
	double price;
	};
	inflat *in = new inflat;
	cout << "enter name of inflatable item:";
	cin.get(in->name, 20).get();
	cout << "enter volume in feet:";
	cin >> (*in).volume;
	cout << "enter price:";
	cin >> in->price;
	cout << "name:" << in->name << "volume=" << in->volume << "price:" << in->price << endl;

	double a1[4] = { 1.2, 2.4, 3.6, 4.8 };
	vector <double>a2(4);
	a2[0] = 1.0 / 2.0;
	a2[1] = 1.0 / 5.0;
	a2[2] = 1.0 / 7.0;
	a2[3] = 1.0 / 9.0;
	array<double, 4>a3 = { 3.14, 2.72, 1.62, 1.41 };
	array<double,4>a4;
	a4 = a3;
	char word[20];
	cin.getline(word, 20);
	cout << word << endl;
	cin.get(word, 20);
	cout << word << endl;

	ofstream out;
	out.open("e:\helloworld.txt");
	out << "hello";
	cout << "hello";
	ofstream outFile;               // create object for output
	outFile.open("aaaa.txt");    // associate with a file
	out.close();
	string name;
	cout << "enter name of data file:";
	cin >> name;
	ifstream in;
	in.open(name);
	if (!in.is_open())
	{
	cout << "the file is not exit";
	exit(EXIT_FAILURE);
	}
	float sum=0,average=0,value=0;
	int cnt = 0;
	in >> value;
	while (in.good())
	{
	cout << value;
	cnt++;
	sum += value;
	in >> value;
	}
	cout << "\nsum:" << sum << ",cnt:" << cnt << "average=" << sum / cnt << endl;
	
double ar[]{1112.3, 1542.6, 2227.3};
	array<double, 4>ary = { 1112.3, 1542.6, 2227.3 };
	const double *(*p1)(const double*, int) = f1;
	auto p2 = f2;
	cout << (*p1)(ar, 3)<<endl;
	cout << p2(ar, 3) << endl;
char *left(const char *str, int n=1);
   char str[20];
   cout << "enter a string:";
   cin.get(str, 20);
   char *p;
   p = left(str, 4);
   cout << p << endl;
   delete[]p;
   p = left(str);
   cout << p << endl;
   delete[]p;*/
	return 0;
}
char *left(const char *str, int n)
{
	int i;
	if (n < 0)
		n = 0;
	char *p = new char[n + 1];
	for ( i = 0; i < n&&str[i]; i++)
		p[i] = str[i];
	while (i <= n)
		p[i++] = '\0';
	return p;
}