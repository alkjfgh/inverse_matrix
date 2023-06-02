#include <iostream>
#include <vector>
#define LINE "==========================================================================="
using namespace std;

struct Matrix {
	vector<vector<double>> v;
	int N;

	//생성
	Matrix(int n) : N(n) {
		v.resize(N, vector<double>(N, 0));
	}

	//소멸
	~Matrix() {
		for (int i = 0; i < N; i++)
			v[i].clear();
		v.clear();
	}

	//단위 행렬 생성
	Matrix unit(int n) {
		Matrix unit = Matrix(n);
		for (int i = 0; i < n; i++)
			unit.v[i][i] = 1;
		return unit;
	}

	//스왑
	void swapRow(int i, int j) {
		if (i == j) return;
		for (int k = 0; k < N; k++)
			swap(v[i][k], v[j][k]);
	}

	//연산자 오버로딩
	double* operator[](int i) { return &v[i][0]; }
};

//사이즈 입력
int inputSize() {
	int size;
	cout << "ENTER SIZE OF MATRIX : ";
	cin >> size;
	return size;
}

//행렬 입력
Matrix inputMatrix(int size) {
	Matrix m(size);
	cout << "ENTER MATRIX : \n";
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> m[i][j];
	return m;
}

//결과 출력
void printMatrix(Matrix& result, int size) {
	cout << LINE << endl;
	//cout.precision(8);
	for (int i = 0; i < size; i++, cout << endl) {
		cout << "|";
		for (int j = 0; j < size; j++) {
			cout.width(10);
			cout << result[i][j];
			cout << '|';
		}
		if (i != size - 1) {
			cout << endl << ' ';
			for (int j = 0; j < size; j++) {
				cout << "-----------";
			}
		}
	}
	cout << LINE << endl;
	cout << "\n";
}

//테스트용
void testPrint(Matrix& input_matrix, Matrix& unit_matrix, int count, int size) {
	cout << "\n=======" << count << "===========\n";
	for (int i = 0; i < size; i++, cout << endl) {
		for (int j = 0; j < size; j++) printf("%4.2lf ", input_matrix[i][j]);
		cout << " | ";
		for (int j = 0; j < size; j++) printf("%4.2lf ", unit_matrix[i][j]);
	}
	cout << "=======" << count << "===========\n";
}

//역행렬 찾기
void getInverseMatrix(Matrix& input_matrix, Matrix& unit_matrix, int size) {
	for (int k = 0; k < size; k++) {
		int t = k - 1;

		//역행렬 존재 체크
		//모든 열이 0이면 역행렬 x
		while (t + 1 < size && !input_matrix[++t][k]);
		if (t == size - 1 && !input_matrix[t][k]) {
			cout << "NO INVERSE" << '\n';
			exit(0);
		}

		//행 스왑
		input_matrix.swapRow(k, t), unit_matrix.swapRow(k, t);
		//testPrint(input_matrix, unit_matrix, 1, size);

		//대각선 원소 1로
		double d = input_matrix[k][k];
		for (int j = 0; j < size; j++)
			input_matrix[k][j] /= d, unit_matrix[k][j] /= d;
		//testPrint(input_matrix, unit_matrix, 2, size);

		//행렬 갱신(0으로 만들기)
		for (int i = 0; i < size; i++) {
			if (i != k) {
				double m = input_matrix[i][k];
				for (int j = 0; j < size; j++) {
					if (j >= k) input_matrix[i][j] -= input_matrix[k][j] * m;
					unit_matrix[i][j] -= unit_matrix[k][j] * m;
				}
			}
		}
		//testPrint(input_matrix, unit_matrix, 3, size);
	}
}

int main() {
	//사이즈 입력
	int size = inputSize();

	//행렬 입력 및 구조체 생성
	Matrix input_matrix = inputMatrix(size);
	Matrix unit_matrix(size);
	unit_matrix = unit_matrix.unit(size);

	//역행렬 구하기
	getInverseMatrix(input_matrix, unit_matrix, size);

	//역행렬 출력
	printMatrix(unit_matrix, size);
}
