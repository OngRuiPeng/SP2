#ifndef UTILITY_H
#define UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"
#include <string>
#include <sstream>
#include <iomanip>

Position operator*(const Mtx44& lhs, const Position& rhs);
std::string Convert (float number);
std::string Converts (float number);

#endif