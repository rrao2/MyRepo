//CS 590 Final Project CWID - 10404926
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define f first
#define s second
#define pair1 pair<int, int>

using namespace std;
const int N = 1000000;
string st;
vector< vector<pair1 > > in, out;
vector<int> Node, FIX;
char g[1001][1001], h[1001][1001];
char a[1001][1001];
int n, m;
int dist_x = 2, dist_y = 2;
int lhs, up, dwn, rhs, ff, ss; //frst and sec
int arr[1001][1001], arr0[1001][1001], arr1[1001][1001], d[1001][1001];
pair1 LS[1001][1001], BG[1001][1001];
queue<pair1> q;
pair1 src[1001][1001]; // for source

void graph_solve();
void print();
void Shortest_path(int x, int y, pair1 z);
void go_to(pair1 A, pair1 B);
int length(int x);
string Str(int x);
void position(int check, int A, int B, int val, int x, int l, int r);
int main() {
	//open file stream to read file
	
	ifstream fin;
	fin.open("graph.dat");
	
	in.resize(N);
	out.resize(N);
	
	while (getline(fin, st))//read everyline
	{
		vector<int> vec;
		int num = 0;
		for (int i = 0; i < st.size(); i++)
		{
			if (st[i] == ' ')
				vec.push_back(num), num = 0;//push into vector
			else
				if (st[i] >= '0' && st[i] <= '9') num = num * 10 + st[i] - '0';
		}
		vec.push_back(num);

		int v = vec[0];//v is first element 
		for (int i = 1; i < vec.size(); i += 2)
		{
			out[v].push_back(make_pair(vec[i], vec[i + 1]));
			in[vec[i]].push_back(make_pair(v, vec[i + 1]));
		}
		
		//position();
	}
	graph_solve();
	//graph_solve func declaration
	system("pause");
	return 0;
}
//end of main 

//Ascii chart printing 



void algo(int v) {
	for (int i = 0; i < Node.size(); i++) {
		arr[v][Node[i]] = 1000000000;
	}
	arr[v][v] = 0;
	set<pair<int, int> > pr;
	pr.insert(make_pair(0, v));
	while (!pr.empty()) {
		int p = pr.begin()->second;
		pr.erase(pr.begin());

		for (int i = 0; i < out[p].size(); i++)
		{
			int to = out[p][i].first;
			int len = out[p][i].second;

			if (arr[v][p] + len < arr[v][to]) {
				pr.erase(make_pair(arr[v][to], to));
				arr[v][to] = arr[v][p] + len;
				pr.insert(make_pair(arr[v][to], to));
			}
		}
	}

	for (int i = 0; i < Node.size(); i++) {
		if (arr[v][Node[i]] == 1000000000) arr[v][Node[i]] = 0;
	}
}

void print()
{
	for (int i = 0; i <= n + 10; i++)
	{
		for (int j = 0; j <= m + 10; j++)
			cout << a[i][j]; cout << endl;
	}
	cout << "   ";
	for (int i = Node.size() - 1; i >= 0; i--)
		cout << Node[i] << " ";
	cout << endl;
	for (int i = Node.size() - 1; i >= 0; i--)
		cout << "___";
	cout << endl;

	for (int i = Node.size() - 1; i >= 0; i--) {
		cout << Node[i] << " | ";
		for (int j = Node.size() - 1; j >= 0; j--)
			cout << arr[Node[i]][Node[j]] << " ";
		cout << endl;
	}

	ofstream w;
	w.open("output.txt");
	for (int i = 0; i <= n + 10; i++)
	{
		for (int j = 0; j <= m + 10; j++)
			w << a[i][j]; w << endl;
	}

	w << "   ";
	for (int i = Node.size() - 1; i >= 0; i--)
		w << Node[i] << " ";
	w << endl;
	for (int i = Node.size() - 1; i >= 0; i--)
		w << "___";
	w << endl;
	for (int i = Node.size() - 1; i >= 0; i--) {
		w << Node[i] << "|";
		for (int j = Node.size() - 1; j >= 0; j--)
			w << arr[Node[i]][Node[j]] << " ";
		w << endl;
	}
}

void graph_solve()
{
	
	for (int v = N - 1; v >= 0; v--)
		if (in[v].size() + out[v].size())
		{
			Node.push_back(v);
			vector<int> numbers;
			for (int i = 0; i<in[v].size(); i++)
				numbers.push_back(length(in[v][i].s));
			for (int i = 0; i<out[v].size(); i++)
				numbers.push_back(length(out[v][i].s));

			int midx = n + 6 + dist_x;
			int midy = m + 5 + dist_y + length(numbers[0]);

			a[midx][midy] = '[';
			string c = Str(v);
			for (int i = midy + 1; i <= midy + c.size(); i++)
				a[midx][i] = c[i - midy - 1];
			a[midx][midy + c.size() + 1] = ']';
			FIX.resize(6);
			FIX.clear();
			FIX.resize(6);
			up = midx - 1;
			dwn = midx + 1;
			lhs = midy - 1;
			rhs = midy + c.size() + 2;

			for (int i = 0; i<in[v].size(); i++)
				position(1, v, in[v][i].f, in[v][i].s, midx, midy, midy + c.size() + 1);

			for (int i = 0; i<out[v].size(); i++)
				position(0, v, out[v][i].f, out[v][i].s, midx, midy, midy + c.size() + 1);

			n = dwn;
			m = rhs;
			for (int i = up; i <= dwn; i++)
				for (int j = lhs; j <= rhs; j++)
					arr0[i][j] = 1;
		}

	for (int i = 0; i<N; i++)
		for (int j = 0; j < out[i].size(); j++)
		{
			ff = i;
			ss = out[i][j].f;
			go_to(BG[i][out[i][j].f], LS[i][out[i][j].f]);
		}

	for (int i = 0; i <= n + 10; i++)
		for (int j = 0; j <= m + 10; j++)
			if (!a[i][j])
				if (g[i][j] && h[i][j])
					a[i][j] = '+';
				else if (g[i][j]) a[i][j] = g[i][j];
				else
					if (h[i][j])
						a[i][j] = h[i][j];
					else   a[i][j] = ' ';


					for (int i = 0; i <= n + 10; i++)
						for (int j = 0; j <= m + 10; j++)
						{
							if (a[i][j] == '|')
							{
								if (a[i][j - 1] == '-' && a[i][j + 1] == '-') a[i][j] = '=';
								else if (a[i][j - 1] == '-') a[i][j] = '+';
								else if (a[i][j + 1] == '-') a[i][j] = '+';

							}
							else
								if (a[i][j] == '-')
								{
									if (a[i - 1][j] == '|' && a[i + 1][j] == '|') a[i][j] = '=';
									else
										if (a[i - 1][j] == '|' || a[i + 1][j] == '|') a[i][j] = '+';
								}
								else
									if (a[i][j] == '+')
									{
										if (a[i - 1][j] == '|' && a[i + 1][j] == '|' && a[i][j - 1] == '-' && a[i][j + 1] == '-')
											a[i][j] = '=';
										else
										{
											if (a[i][j - 1] == ' ' && a[i][j + 1] == ' ')
												a[i][j] = '|';

											if (a[i + 1][j] == ' ' && a[i - 1][j] == ' ')
												a[i][j] = '-';
										}
									}
						}
					for (int i = 0; i < Node.size(); i++)
						algo(Node[i]);
					print();
}

int length(int x)
{
	int X = 0;
	while (x != 0)
	{
		X++;
		x /= 10;
	}
	return X;
}

string Str(int x)
{
	string out;
	while (x != 0)
	{
		out += char('0' + x % 10);
		x /= 10;
	}
	reverse(out.begin(), out.end());
	return out;
}

void position(int check, int A, int B, int val, int x, int l, int r)
{
	int pos = 0;

	if (!FIX[1])//if not 1
	{
		if (check) //if check is not false
			a[x][r + 1] = '<', pos = 1, a[x][r + 2] = '-';
		else
			a[x][r + 1 + pos] = '-';
		string c = Str(val);
		if (check)
		{
			for (int i = r + 2; i <= r + c.size() + 1; i++)
				a[x][i + pos] = '-';
		}
		else
		{
			for (int i = r + 2; i <= r + c.size() + 1; i++)
				a[x][i + pos] = c[i - r - 2];
		}

		a[x][r + c.size() + 2 + pos] = '-';
		rhs = r + c.size() + 2 + pos;
		a[x][r + c.size() + 3 + pos] = '+';

		if (check)
		{
			LS[B][A] = make_pair(x, r + c.size() + 3 + pos);
			arr[B][A] += c.size() + 3 + pos;
		}
		else
		{
			BG[A][B] = make_pair(x, r + c.size() + 3 + pos);
			arr[A][B] += c.size() + 3 + pos;
		}

		FIX[1] = 1;
		return;
	}


	if (!FIX[2])
	{
		if (check) a[x - 1][(l + r) / 2] = 'V', a[x - 2][(l + r) / 2] = '|', pos = 1; else
			a[x - 1 - pos][(l + r) / 2] = '|';
		string c = Str(val);
		if (check)a[x - 2 - pos][(l + r) / 2] = '|'; 
		else
		{
			for (int i = 0; i<c.size(); i++)
				a[x - 2 - pos][(l + r) / 2 - c.size() / 2 + i] = c[i];
		}
		a[x - 3 - pos][(l + r) / 2] = '|';
		up = x - 3 - pos;
		a[x - 4 - pos][(l + r) / 2] = '+';
		if (check)
		{
			LS[B][A] = make_pair(x - 4 - pos, (l + r) / 2);
			arr[B][A] += 4 + pos;
		}
		else
		{
			BG[A][B] = make_pair(x - 4 - pos, (l + r) / 2);
			arr[A][B] += 4 + pos;
		}

		FIX[2] = 1;
		return;
	}

	if (!FIX[3])
	{
		if (check) a[x + 1][(l + r) / 2] = '^', a[x + 2][(l + r) / 2] = '|', pos = 1; else
			a[x + 1 + pos][(l + r) / 2] = '|';
		string c = Str(val);
		if (check)a[x + 2 + pos][(l + r) / 2] = '|'; else
			for (int i = 0; i<c.size(); i++)
				a[x + 2 + pos][(l + r) / 2 - c.size() / 2 + i] = c[i];

		a[x + 3 + pos][(l + r) / 2] = '|';
		dwn = x + 3 + pos;
		a[x + 4 + pos][(l + r) / 2] = '+';
		if (check)
		{
			LS[B][A] = make_pair(x + 4 + pos, (l + r) / 2);
			arr[B][A] += 4 + pos;
		}
		else
		{
			BG[A][B] = make_pair(x + 4 + pos, (l + r) / 2);
			arr[A][B] += 4 + pos;
		}

		FIX[3] = 1;
		return;
	}
	if (!FIX[0])
	{
		if (check) a[x][l - 1] = '>', a[x][l - 2] = '-', pos = 1; else
			a[x][l - 1] = '-';
		string c = Str(val);
		if (check) { 
			for (int i = l - 2; i >= l - c.size() - 1; i--)a[x][i - pos] = '-'; 
		}
		else
		{
			for (int i = l - 2; i >= l - c.size() - 1; i--)
				a[x][i - pos] = c[i - l + c.size() + 1];
		}
		a[x][l - c.size() - 2 - pos] = '-';
		lhs = l - c.size() - 2 - pos;
		a[x][l - c.size() - 3 - pos] = '+';
		if (check)
		{
			LS[B][A] = make_pair(x, l - c.size() - 3 - pos);
			arr[B][A] += c.size() + 3 + pos;
		}
		else
		{
			BG[A][B] = make_pair(x, l - c.size() - 3 - pos);
			arr[A][B] += c.size() + 3 + pos;
		}
		FIX[0] = 1;
		return;
	}
}

void Shortest_path(int x, int y, pair1 z)
{
	if (1 <= x && x <= 100 && 1 <= y && y <= 100)
		if (!arr1[x][y])
		{
			arr1[x][y] = 1;
			q.push(make_pair(x, y));
			d[x][y] = d[z.f][z.s] + 1;
			src[x][y] = z;
		}
}

void go_to(pair1 A, pair1 B)
{
	while (!q.empty()) q.pop();
	q.push(A);
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= 1000; j++)
			arr1[i][j] = arr0[i][j], src[i][j].f = 0, src[i][j].s = 0;
	arr1[A.f][A.s] = 1;


	while (!q.empty())
	{
		pair1 pair_1 = q.front();
		if (pair_1 == B) break;
		q.pop();
		Shortest_path(pair_1.f - 1, pair_1.s, pair_1);
		Shortest_path(pair_1.f + 1, pair_1.s, pair_1);
		Shortest_path(pair_1.f, pair_1.s + 1, pair_1);
		Shortest_path(pair_1.f, pair_1.s - 1, pair_1);
	}

	vector<pair1> myv;
	while (true)
	{
		myv.push_back(B);
		if (src[B.f][B.s] == A)break;
		B = src[B.f][B.s];
	}
	myv.push_back(A);
	reverse(myv.begin(), myv.end());


	for (int i = 0; i + 1<myv.size(); i++)
	{
		if (i == myv.size() - 1 || myv[i].f == myv[i + 1].f)
			g[myv[i].f][myv[i].s] = '-'; else
			h[myv[i].f][myv[i].s] = '|';
	}
	arr[ff][ss] += myv.size();
}