#include <iostream>
#include <vector>
#define LINE "==========================================================================="
using namespace std;

struct Matrix {
	vector<vector<double>> v;
	int N;

	//����
	Matrix(int n) : N(n) {
		v.resize(N, vector<double>(N, 0));
	}

	//�Ҹ�
	~Matrix() {
		for (int i = 0; i < N; i++)
			v[i].clear();
		v.clear();
	}

	//���� ��� ����
	Matrix unit(int n) {
		Matrix unit = Matrix(n);
		for (int i = 0; i < n; i++)
			unit.v[i][i] = 1;
		return unit;
	}

	//����
	void swapRow(int i, int j) {
		if (i == j) return;
		for (int k = 0; k < N; k++)
			swap(v[i][k], v[j][k]);
	}

	//������ �����ε�
	double* operator[](int i) { return &v[i][0]; }
};

//������ �Է�
int inputSize() {
	int size;
	cout << "ENTER SIZE OF MATRIX : ";
	cin >> size;
	return size;
}

//��� �Է�
Matrix inputMatrix(int size) {
	Matrix m(size);
	cout << "ENTER MATRIX : \n";
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> m[i][j];
	return m;
}

//��� ���
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

//�׽�Ʈ��
void testPrint(Matrix& input_matrix, Matrix& unit_matrix, int count, int size) {
	cout << "\n=======" << count << "===========\n";
	for (int i = 0; i < size; i++, cout << endl) {
		for (int j = 0; j < size; j++) printf("%4.2lf ", input_matrix[i][j]);
		cout << " | ";
		for (int j = 0; j < size; j++) printf("%4.2lf ", unit_matrix[i][j]);
	}
	cout << "=======" << count << "===========\n";
}

//����� ã��
void getInverseMatrix(Matrix& input_matrix, Matrix& unit_matrix, int size) {
	for (int k = 0; k < size; k++) {
		int t = k - 1;

		//����� ���� üũ
		//��� ���� 0�̸� ����� x
		while (t + 1 < size && !input_matrix[++t][k]);
		if (t == size - 1 && !input_matrix[t][k]) {
			cout << "NO INVERSE" << '\n';
			exit(0);
		}

		//�� ����
		input_matrix.swapRow(k, t), unit_matrix.swapRow(k, t);
		//testPrint(input_matrix, unit_matrix, 1, size);

		//�밢�� ���� 1��
		double d = input_matrix[k][k];
		for (int j = 0; j < size; j++)
			input_matrix[k][j] /= d, unit_matrix[k][j] /= d;
		//testPrint(input_matrix, unit_matrix, 2, size);

		//��� ����(0���� �����)
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
	//������ �Է�
	int size = inputSize();

	//��� �Է� �� ����ü ����
	Matrix input_matrix = inputMatrix(size);
	Matrix unit_matrix(size);
	unit_matrix = unit_matrix.unit(size);

	//����� ���ϱ�
	getInverseMatrix(input_matrix, unit_matrix, size);

	//����� ���
	printMatrix(unit_matrix, size);
}
