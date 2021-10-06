#pragma once
#include "dynamicArray.h"
#include "../Domain/tutorial.h"

class Repository{
    private:
        DynamicArray<Tutorial>* data;

    public:

    /// Constructor
    /// \param data: pointer to the dynamic array
    Repository(DynamicArray<Tutorial>* data);

    /// Destructor
    ~Repository();

    /// Adds an element to the repository
    /// \param element: a given element
    void addElement(Tutorial element);

    /// Deletes the element found at a given position from the repository
    /// \param position: a given position
    void deleteElement(int position);

    /// Updates the element found at a given position from the repository
    /// \param position: a given position
    /// \param new_likes: a new number of likes
    void updateElement(int position, int new_likes);

    /// Initializes the repository
    void initRepository();

    /// Returns the dynamic array from the repository
    DynamicArray<Tutorial>* getArray() const;
};