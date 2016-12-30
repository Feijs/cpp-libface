#if !defined LIBFACE_DATA_CONTAINER_HPP
#define LIBFACE_DATA_CONTAINER_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <assert.h>

#include <include/phrase_map.hpp>
#include <include/types.hpp>

using namespace std;

class DataContainer {
public:
    PhraseMap pm;           // Phrase Map (usually a sorted array of strings)
    RMQ st;                 // An instance of the RMQ Data Structure
    char *if_mmap_addr;     // Pointer to the mmapped area of the file
    off_t if_length;        // The length of the input file
    volatile bool building; // TRUE if the container structure is being built

public:
    DataContainer() {
        this->if_mmap_addr = NULL;
        this->if_length = 0;
        this->building = false;
    }

    size_t 
    finalize() {
        this->pm.finalize();

        vui_t weights;
        for (size_t i = 0; i < this->pm.repr.size(); ++i) {
            weights.push_back(this->pm.repr[i].weight);
        }

        this->st.initialize(weights);

        return weights.size();
    }
};

#endif // LIBFACE_DATA_CONTAINER_HPP
