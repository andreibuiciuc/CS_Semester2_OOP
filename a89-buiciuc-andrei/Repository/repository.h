#pragma once
#include <vector>
#include "../Domain/tutorial.h"

typedef Tutorial TElem;

class Repository {
protected:
    std::vector<TElem> data;

public:

    Repository();

    Repository(const Repository& repository);

    virtual ~Repository();

    /// Adds an element to the array
    /// \param element: a given element
    virtual void addElement(const TElem& element);

    /// Deletes the element from a given position
    /// \param position: a given position
    virtual void deleteElement(int position);

    /// Updates the element from a given position with a new number of likes
    virtual void updateElement(int position, int newLikes);

    /// Gets the length of the array
    int getLength() const;

    /// Gets the elements from the array
    std::vector<TElem> getData() const;

    int findElement(const std::string& title, const std::string& presenter);

    /// Initializes the repository
    void initRepository();
};
