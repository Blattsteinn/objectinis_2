
template <typename T>
bool Vector<T>::operator==(const Vector& other) const {
    if (size_ != other.size_) return false;

    return std::equal(begin(), end(), 
              other.begin(), other.end());
 }

template <typename T>
bool Vector<T>::operator!=(const Vector& other) const {
    return !(other == *this);
 }

template <typename T>
bool Vector<T>::operator>(const Vector& other) const {
    // true if the first range is lexicographically less than the second, otherwise false.  
    // Note: always uses < (so it's -  other < this)
   return std::lexicographical_compare(other.begin(), other.end(),   // first range  (other)
                                       begin(), end());              // second range (*this)
 }

template <typename T>
bool Vector<T>::operator>=(const Vector& other) const {
    return !std::lexicographical_compare(begin(),      end(),
                                         other.begin(), other.end()
    );
}

template <typename T>
bool Vector<T>::operator<(const Vector& other) const {
   return std::lexicographical_compare(begin(), end(), 
                                       other.begin(), other.end());
 }

template <typename T>
bool Vector<T>::operator<=(const Vector& other) const {
    return !std::lexicographical_compare(other.begin(), other.end(),
                                         begin(), end());
}