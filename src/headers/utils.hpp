#include <algorithm>
#include <iostream>
#include <map>
#pragma once

#define enlist(x) std::begin(x), std::end(x)

template<class B, class E, class Elem>
bool contains(const B& begin, const E& end, const Elem& elem)
{ return std::find(begin, end, elem) != end; }

template<class C, class Elem>
bool contains(const C& container, const Elem& elem)
{ return contains(enlist(container), elem); }

template<typename K, typename V> bool contains(std::map<K, V> map, K key)
{ return map.find(key) != map.end(); }