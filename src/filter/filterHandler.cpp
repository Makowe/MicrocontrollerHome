//
// Created by nicom on 12/14/2022.
//

#include "filterHandler.h"
#include <filter/instances/filterNothing.h>
#include <filter/instances/filterPulsate.h>

FilterPulsate filterPulsate = FilterPulsate(PULSATE_DEFAULT_SPEED);
FilterNothing filterNothing = FilterNothing();

Filter* currentFilter = &filterPulsate;

void initFilters() {
    filterPulsate.nextFilter = &filterNothing;
    filterNothing.nextFilter = &filterPulsate;
}

void selectNextFilter() {
    currentFilter = currentFilter->nextFilter;
}
