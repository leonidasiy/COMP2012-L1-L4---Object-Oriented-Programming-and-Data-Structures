#include "BinarySearchTree.h"
using namespace std;

BinarySearchTree::BinarySearchTree(int score, int studentId, bool isRoot) : 
    score(score), studentId(studentId), isRoot(isRoot), leftSubTree(nullptr), rightSubTree(nullptr) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : score(other.score), studentId(other.studentId), isRoot(other.isRoot), leftSubTree(nullptr), rightSubTree(nullptr) {
    // TODO #1: Copy constructor
    if (other.leftSubTree) {
        leftSubTree = new BinarySearchTree(*other.leftSubTree);
    }
    if (other.rightSubTree) {
        rightSubTree = new BinarySearchTree(*other.rightSubTree);
    }
}

BinarySearchTree::~BinarySearchTree() {
    // TODO #2: Destructor
    delete leftSubTree;
    delete rightSubTree;
}

bool BinarySearchTree::findByScore(int score) const {
    // TODO #3: Search by score
    bool found = false;

    if (score == this->score) {
        found = true;
        printStudentInfo();
    } else {
        BinarySearchTree* next = score < this->score ? this->leftSubTree : this->rightSubTree;
        while(next) {
            if (score == next->score) {
                found = true;
                next->printStudentInfo();
                break;
            } else {
                next = score < next->score ? next->leftSubTree : next->rightSubTree;
            }
        }
    }

    if (!found) {
        printFailedInfo();
    }
    return found;
}

void BinarySearchTree::insert(int score, int studentId) {
    // TODO #4: Insert a node
    // bool success = false;

    if (score < this->score) {
        if (this->leftSubTree) {
            this->leftSubTree->insert(score, studentId);
        } else {
            this->leftSubTree = new BinarySearchTree(score, studentId, false);
            cout << "Inserted successfully." << endl;
            // success = true;
        }
    } else if (score > this->score) {
        if (this->rightSubTree) {
            this->rightSubTree->insert(score, studentId);
        } else {
            this->rightSubTree = new BinarySearchTree(score, studentId, false);
            cout << "Inserted successfully." << endl;
            // success = true;
        }
    } else {
        cout << "Skipping due to a duplicate." << endl;
    }

    // if (success) {
    //     cout << "Inserted successfully." << endl;
    // } else {
    //     cout << "Skipping due to a duplicate." << endl;
    // }
}

void BinarySearchTree::inorderTraversal() const {
    // TODO #5: In-order traversal 
    if (this->leftSubTree) {
        this->leftSubTree->inorderTraversal();
    }
    printStudentInfo();
    if (this->rightSubTree) {
        this->rightSubTree->inorderTraversal();
    }
}

void BinarySearchTree::printAllScoreBelow(int threshold) const {
    // TODO #6: Print students below a threshold score
    if (this->leftSubTree) {
        this->leftSubTree->printAllScoreBelow(threshold);
    }
    if (score < threshold) {
        printStudentInfo();
    }
    if (this->rightSubTree) {
        this->rightSubTree->printAllScoreBelow(threshold);
    }
}

// Provided utility functions (no modification needed)
void BinarySearchTree::printStudentInfo() const {
    cout << "Student Info: [SID: " << studentId << ", Score: " << score << "]." << endl;
}


void BinarySearchTree::printFailedInfo() const {
    cout << "Student not found." << endl;
}