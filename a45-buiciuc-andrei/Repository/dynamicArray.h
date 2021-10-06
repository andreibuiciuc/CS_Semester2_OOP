#pragma once

template <typename TElem>
class DynamicArray {
    private:
        int capacity;
        int length;
        TElem* elements;

    public:

    /// Constructor
    /// \param capacity: a given capacity for the array of elements.
    DynamicArray(int capacity);

    /// Copy constructor
    DynamicArray(const DynamicArray& array);

    /// Destructor
    ~DynamicArray();

    /// Adds an element to the array.
    /// \param element: a new element.
    void addElement(TElem element);

    /// Deletes the element found on a given position from the array.
    /// \param position: a given position
    void deleteElement(int position);

    /// Updates the element found on a given position from the array.
    /// \param position: a given position
    /// \param new_likes: a new number of likes
    void updateElement(int position, int new_likes);

    /// Gets the capacity of the array.
    int getCapacity();

    /// Gets the length of the array.
    int getLength();

    /// Gets the elements from the array.
    TElem* getData();

    private:

    /// Resizes the array of elements.
    void resizeArray();
};

template <typename TElem>
DynamicArray<TElem>::DynamicArray(int capacity) {
    this->capacity = capacity;
    this->length = 0;
    this->elements = new TElem[capacity];
}

template <typename TElem>
DynamicArray<TElem>::DynamicArray(const DynamicArray<TElem> &array) {
    this->capacity = array.capacity;
    this->length = array.length;
    this->elements = new TElem [this->capacity];
    for(int index = 0; index < array.length; index ++) {
        this->elements[index] = array.elements[index];
    }
}

template <typename TElem>
DynamicArray<TElem>::~DynamicArray() {
    delete[] this->elements;
}

template <typename TElem>
void DynamicArray<TElem>::addElement(TElem element) {
    if(this->length == this->capacity){
        this->resizeArray();
    }

    this->elements[this->length] = element;
    this->length += 1;
}

template <typename TElem>
void DynamicArray<TElem>::deleteElement(int position) {
    if(position < this->length) {
        this->length -= 1;
        for(int index = position; index < this->length; index ++){
            this->elements[index] = this->elements[index + 1];
        }
    }
}

template <typename TElem>
void DynamicArray<TElem>::updateElement(int position, int new_likes) {
    this->elements[position].set_likes(new_likes);
}

template <typename TElem>
int DynamicArray<TElem>::getCapacity() { return this->capacity; }

template <typename TElem>
int DynamicArray<TElem>::getLength() { return this->length; }

template <typename TElem>
TElem* DynamicArray<TElem>::getData() { return this->elements; }

template <typename TElem>
void DynamicArray<TElem>::resizeArray() {
    this->capacity = this->capacity * 2;
    TElem* newElements = new TElem [this->capacity];

    for(int i = 0; i < this->length; i ++){
        newElements[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newElements;
}