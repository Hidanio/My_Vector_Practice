#include <iostream>
#include <vector>
#include <memory>

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired\n";
    }

    ~Resource() {
        std::cout << "Resource released\n";
    }
};

class Dependent {
private:
    Resource *resource;
public:
    Dependent(Resource *res) : resource(res) {
        std::cout << "Dependent created\n";
    }

    ~Dependent() {
        std::cout << "Dependent destroyed\n";
// Imagine that Dependent needs Resource to do some cleanup
    }
};

void incorrect_destruction_order() {
    std::vector<std::unique_ptr<Dependent>> dependents;
    std::vector<std::unique_ptr<Resource>> resources;

    for (int i = 0; i < 3; ++i) {
        resources.push_back(std::make_unique<Resource>());
        dependents.push_back(std::make_unique<Dependent>(resources.back().get()));
    }

// Incorrect destruction order (implicitly happens if vectors are cleared in order)
    dependents.clear(); // Destroy dependents first
    resources.clear(); // Then destroy resources
}

void correct_destruction_order() {
    std::vector<std::unique_ptr<Dependent>> dependents;
    std::vector<std::unique_ptr<Resource>> resources;

    for (int i = 0; i < 3; ++i) {
        resources.push_back(std::make_unique<Resource>());
        dependents.push_back(std::make_unique<Dependent>(resources.back().get()));
    }

// Correct destruction order (implicitly happens if vectors are cleared in reverse order)
    resources.clear(); // Destroy resources first
    dependents.clear(); // Then destroy dependents
}

void run_destruction_experiment() {
    std::cout << "Incorrect destruction order:\n";
    incorrect_destruction_order();

    std::cout << "\nCorrect destruction order:\n";
    correct_destruction_order();
}
