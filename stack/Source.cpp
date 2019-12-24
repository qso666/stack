#include <exception>
#include <iostream>
template <typename T>
class stack {
public:
	stack() {
		data = nullptr;
		size = 0;
	}

	stack(const stack&) = delete;

	stack(stack&& rhs) {
		data = rhs.data;
		size = rhs.size;
		rhs.data = nullptr;
		rhs.size = 0;
	}

	~stack() {
		if (data != nullptr) { delete[] data; }
		size = 0;
	}

	stack& operator=(const stack&) = delete;

	void push(T&& value) {
		T* pam = new T[size + 1];
		for (size_t i = 0; i < size; i++) {
			pam[i] = data[i];
		}
		pam[size] = std::move(value);
		if (data != nullptr) { delete[] data; }
		data = pam;
		size++;
	}

	void push(const T& value) {
		T* pam = new T[size + 1];
		for (size_t i = 0; i < size; i++) {
			pam[i] = data[i];
		}
		pam[size] = value;
		if (data != nullptr) { delete[] data; }
		data = pam;
		size++;
	}

	void pop() {
		if (data == nullptr) {
			throw std::logic_error("Empty");
		}
		size--;
		T* pam = new T[size];
		for (size_t i = 0; i < size; i++) {
			pam[i] = data[i];
		}
		delete[] data;
		data = pam;
	}

	const T& head() const {
		if (data == nullptr) {
			throw std::logic_error("Empty");
		}
		return data[size - 1];
	}

	// formal parametr
	T pop(int) {
		if (data == nullptr) {
			throw std::logic_error("Empty");
		}
		size--;
		T pam2 = data[size];
		T* pam = new T[size + 1];
		for (size_t i = 0; i < size; i++) {
			pam[i] = data[i];
		}
		delete[] data;
		data = pam;
		return pam2;
	}

	template <typename ... Args>
	void push_emplace(Args&& ... value) {
		T* pam = new T[size + 1];
		for (size_t i = 0; i < size; i++) {
			pam[i] = data[i];
		}
		pam[size] = std::move(T(value...));
		if (data != nullptr) { delete[] data; }
		data = pam;
		size++;
	}

	stack& operator=(stack&& rhs) {
		if (&rhs == this) { return *this; }
		if (data != nullptr) { delete[] data; }
		data = rhs.data;
		size = rhs.size;
		rhs.data = nullptr;
		rhs.size = 0;
		return *this;
	}

private:
	T* data;
	size_t size;
};
int main()
{
	stack <int> Stack;
	Stack.push(8);
	Stack.push(5);
	Stack.push(6);
	std::cout << Stack.head() << std::endl;
	Stack.pop();
	std::cout << Stack.head() << std::endl;
	Stack.push_emplace<int>(4);
	std::cout << Stack.head() << std::endl;
	return 0;
}

