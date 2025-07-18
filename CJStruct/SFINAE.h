
#ifndef SFINAE_H
#define SFINAE_H

namespace SFINAEgetter {
    template <typename T>
    struct is_vector : std::false_type {};

    template <typename T, typename Alloc>
    struct is_vector<std::vector<T, Alloc>> : std::true_type {};

    template <typename T>
    struct is_map : std::false_type {};

    template <typename Key, typename T, typename Compare, typename Alloc>
    struct is_map<std::map<Key, T, Compare, Alloc>> : std::true_type {};

    template <typename T>
    struct is_tuple : std::false_type {};

    template <typename... Elements>
    struct is_tuple<std::tuple<Elements...>> : std::true_type {};

    template <typename T>
    struct is_pair : std::false_type {};

    template <typename T1, typename T2>
    struct is_pair<std::pair<T1, T2>> : std::true_type {};

    template <typename T>
    struct is_array : std::false_type {};

    template <typename T, size_t N>
    struct is_array<std::array<T, N>> : std::true_type {};

    template <typename T>
    struct is_set : std::false_type {};

    template <typename Key, typename Compare, typename Alloc>
    struct is_set<std::set<Key, Compare, Alloc>> : std::true_type {};

    template <typename T>
    struct is_list : std::false_type {};

    template <typename T, typename Alloc>
    struct is_list<std::list<T, Alloc>> : std::true_type {};

    template <typename T, typename = void>
    struct is_struct : std::false_type {};

    template <class T>
    struct is_struct<T, std::void_t<decltype(std::declval<std::is_class<T>>())>> : std::true_type {};

    template <typename T>
    struct clean_type {
        using type = std::remove_reference_t<T>;
    };
    template <>
    struct clean_type<std::vector<bool>::reference> {
        using type = bool;
    };
}
#endif //SFINAE_H
