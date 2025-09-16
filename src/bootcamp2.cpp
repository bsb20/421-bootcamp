#include <algorithm>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

template <typename T> class SmartArray {
private:
  T* data;
  size_t size;
  std::string name;
  std::shared_mutex mtx;

public:
  SmartArray();
  SmartArray(size_t s, const std::string &n);
  SmartArray(const SmartArray &that);
  SmartArray(SmartArray &&that);

  SmartArray &operator=(const SmartArray &that);
  SmartArray &operator=(SmartArray &&that);

  ~SmartArray();

  void fill(T val);
  void fill(T val, T step);
  void print_contents() const;

  void read_data(int id);
  void write_data(int id, int value);

  size_t get_size() const { return size; }

  T *begin() { return data; }
  T *end() { return data + size; }
  const T *begin() const { return data; }
  const T *end() const { return data + size; }
};

template<typename T> SmartArray<T>::SmartArray() {
  // Default constructor for SmartArray
  // 1. Initializer list that sets data to null and size to 0, and set the name to "Default"
  // 2. Print "Default constructor is called for {name}"
}

template<typename T> SmartArray<T>::SmartArray(size_t s, const std::string &n) {
  // Constructor that allocates memory for s type-T elements and set the name to n
  // 1. Initializer list that sets size to s and name to n
  // 2. Call new to allocate memory for data
  // 3. Print corresponding debug message like: "Constructor allocated {s} elements for SmartArray {name}"
}

template<typename T> SmartArray<T>::SmartArray(const SmartArray &that) {
  // Copy constructor that copies content from another SmartArray
  // 1. Set the size according to that.size
  // 2. Set the name to {that.name}_copied
  // 3. Allocate memory for data
  // 4. Copy the contents of that.data to data
  // 5. Print corresponding debug message
}

template<typename T> SmartArray<T>::SmartArray(SmartArray &&that) {
  // Move constructor that moves content from another SmartArray
  // 1. Set the size according to that.size
  // 2. Set the name to {that.name}_moved
  // 3. Move that.data to data
  // 4. Set the size according to that.size
  // 5. Set that.data to nullptr and that.size to 0 (Why?)
}

template<typename T>
SmartArray<T>& SmartArray<T>::operator=(const SmartArray &that) {
  // Copy assignment that takes care of a = b, both SmartArrays
  // 1. Return if this == &that
  // 2. Delete data if there is any to prevent memory leak
  // 3. Set the size accordingly
  // 4. Set name to {that.name}_copy_assigned
  // 5. Copy data
  // 6. Print corresponding debug message
  return *this;
}

template<typename T>
SmartArray<T>& SmartArray<T>::operator=(SmartArray &&that) {
  // Move assignment that takes care of a = std::move(b), both SmartArrays
  // 1. Return if this == &that
  // 2. Delete data if there is any to prevent memory leak
  // 3. Set the size accordingly
  // 4. Set name to {that.name}_move_assigned
  // 5. Move data
  // 6. Set that.size to 0 and that.data to nullptr (Why?)
  // 6. Print corresponding debug message
  return *this;
}

template<typename T>
SmartArray<T>::~SmartArray() {
  // Destructor for SmartArray
  // 1. Release data
  // 2. Print corresponding debug message
  std::cout << "Destructor called for " << name << std::endl;
  delete[] data;
}

template<typename T>
void SmartArray<T>::read_data(int id) {
  // Read and print all the contents in the SmartArray with thread id `id`
  // 1. Lock the mutex using shared_lock
  // 2. Output Reader {id} is reading
  // 3. Output all the contents in the SmartArray using a for-each loop
}

template<typename T>
void SmartArray<T>::write_data(int id, int value) {
  // Write value into the first element, thread-safe
  // 1. Lock the mutex using unique_lock
  // 2. Output Writer {id} is writing
  // 3. Set the first element in data to value
}

template<typename T>
void SmartArray<T>::fill(T val) {
  fill(val, 1);
}

template<typename T>
void SmartArray<T>::fill(T val, T step) {
  if (size < 1) return;
  data[0] = val;
  for (int i = 1; i < size; ++ i) {
    data[i] = data[i - 1] + step;
  }
}

template<typename T>
void SmartArray<T>::print_contents() const {
  std::stringstream ss;
  ss << "Contents of " << name << " (" << size << " elements): ";
  if (size > 0) {
    for (const T &val : *this) {
      ss << val << " ";
    }
  } else {
    ss << " (empty)";
  }
  std::cout << ss.str() << std::endl;
}

inline void part1() {
  SmartArray<int> default_array;
  SmartArray<int> numbers(6, "Numbers");
  numbers.fill(10, -1);
  std::cout << "Original SmartArray: ";
  numbers.print_contents();

  std::sort(numbers.begin(), numbers.end());
  std::cout << "Sorted SmartArray: ";
  numbers.print_contents();
  std::cout << "---" << std::endl;
}

inline void part2() {
  SmartArray<int> array1(5, "Array1");
  array1.fill(10);
  array1.print_contents();
  std::cout << "---" << std::endl;

  SmartArray<int> array2 = array1;
  array2.print_contents();
  std::cout << "Array2 created as a copy of Array1." << std::endl;
  std::cout << "---" << std::endl;
}

inline void part3() {
  SmartArray<int> array1(5, "Array1");
  array1.fill(10);
  array1.print_contents();

  SmartArray<int> array3;
  array3 = array1;
  array3.print_contents();
  std::cout << "Array3 assigned from Array1." << std::endl;
  std::cout << "---" << std::endl;

  SmartArray<int> array4 = SmartArray<int>(3, "TempArray");
  array4.fill(50);
  std::cout << "Before move, array4 contents: ";
  array4.print_contents();

  array3 = std::move(array4);
  std::cout << "After move, array3 now has contents: ";
  array3.print_contents();
  std::cout << "And array4 is now empty: ";
  array4.print_contents();
  std::cout << "---" << std::endl;
}

inline void part4() {
  SmartArray<int> shared_data(8, "SharedData");
  std::cout << "Starting reader/writer lock example..." << std::endl;

  shared_data.fill(20);

  std::vector<std::thread> threads;

  threads.emplace_back(&SmartArray<int>::read_data, &shared_data, 0);
  threads.emplace_back(&SmartArray<int>::write_data, &shared_data, 100, 7);

  for (int i = 1; i < 3; ++i) {
    threads.emplace_back(&SmartArray<int>::read_data, &shared_data, i);
  }

  for (auto &t : threads) {
    t.join();
  }
  std::cout << "Reader/writer lock example finished." << std::endl;
}

class SmartIntArray {
public:
  SmartIntArray() : data(nullptr), size(0) {}
  SmartIntArray(size_t sz, int fill = 0) : size(sz) {
    data = new int[sz];
    std::fill(data, data + size, fill);
  }
  SmartIntArray(const SmartIntArray &that) {
    std::cout << "copy constructor called" << std::endl;
    size = that.size;
    data = new int[size];
    std::copy(that.begin(), that.end(), data);
  }
  SmartIntArray& operator =(SmartIntArray&& that) {
    std::cout << "move assignment called" << std::endl;
    delete[] data;
    data = std::move(that.data);
    size = that.size;
    that.data = nullptr;
    that.size = 0;
    return *this;
  }
  void set(int ind, int val) {
    if (0 < ind && ind < size) {
      data[ind] = val;
    }
  }
  int* begin() { return data; }
  int* end() { return data + size; }
  const int* begin() const { return data; }
  const int* end() const { return data + size; }
  ~SmartIntArray() {
    delete[] data;
  }
private:
  int *data, size;
};

void part0() {
  SmartIntArray b;
  for (int i = 0; i <= 100; i++) {
    SmartIntArray a(10);
    a.set(3, 123123);
    if (i == 50) b = std::move(a);
  }
  std::cout << b.begin()[3] << std::endl;
  SmartIntArray c = b;
  std::cout << c.begin()[3] << std::endl;
}

int main() {
  part0();
  // part1();
  // part2();
  // part3();
  // part4();

  return 0;
}
