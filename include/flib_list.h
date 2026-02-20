#ifndef FLIB_LIST_H
#define FLIB_LIST_H
#include "flib_definitions.h"

typedef struct flib_list flib_list;

/**
 * @brief Function pointer type to be provided for flib_list_sort().
 */
typedef flib_i32 (* flib_list_compare_func)(const void *lhs, const void *rhs);

#define flib_list_foreach(item, list) for (int i = 0; i < (list)->size && ((item) = flib_list_get_item((list), i)); i++)

/**
 * @brief Creates and allocates a new empty list capable of containing 'capacity' amount of elements.
 * 
 * @param capacity The capacity of the list initialized.
 * @param element_size The size of one element in bytes of the type the list should contain.
 * @return A pointer to the list on success, otherwise NULL.
 */
flib_list *flib_list_alloc(flib_ui32 capacity, flib_ui32 element_size);

/**
 * @brief Destroys and deallocates the provided list.
 * 
 * @param list The list that should be destroyed and deallocated.
 */
void flib_list_dealloc(flib_list **list);

/**
 * @brief Returns the amount of elements currently contained in the list.
 * 
 * @param list The list from which the amount of elements currently contained should be returned.
 * @return Returns the amount of elements currently contained in the list or 0 if list is NULL.
 */
flib_ui32 flib_list_get_size(const flib_list *list);

/**
 * @brief Returns the maximal amount of elements that the list can contain.
 * 
 * @param list The list from which the maximum amount of elements that the list can contain should be returned.
 * @return Returns the maximal amount of elements that list can contain or 0 if list is NULL.
 */
flib_ui32 flib_list_get_capacity(const flib_list *list);

/**
 * @brief Returns whether the list is empty or not.
 * 
 * @param list The list which is whether empty or not.
 * @return Returns 1 if the list is empty or 0 otherwise.
 */
flib_i32 flib_list_is_empty(const flib_list *list);

/**
 * @brief Returns a pointer to the n-th element of the list.
 * 
 * @param list The list from which the n-th element should be returned.
 * @param index The n-th index of the list from which the item should be returned.
 * @return Returns a pointer to the n-th element of the list, if the index is not greater than the actual size of the list.
 *         The pointer needs to be manually casted to the type, the list was created for.
 */
void *flib_list_get_item(const flib_list *list, flib_ui32 index);

/**
 * @brief Sets the n-th element of the list to the value provided.
 * 
 * @param list The list for which the value should be changed.
 * @param index The n-th index of the list for which the value should be changed.
 * @param item The new value to be set.
 */
void flib_list_set_item(flib_list *list, flib_ui32 index, void *item);

/**
 * @brief Appends an item to the end of the list.
 * 
 * @param list The list to which the item should be appended.
 * @param item The item that is appended to the list.
 */
void flib_list_add(flib_list *list, void *item);

/**
 * @brief Removes the last item from the list.
 * 
 * @param list The list from which the last item should be removed.
 */
void flib_list_remove(flib_list *list);

/**
 * @brief Removes the item at n-th index from the list. 
 * 
 * @param list The list from which the element should be removed.
 * @param index The n-th index of the element that should be removed.
 */
void flib_list_remove_at(flib_list *list, flib_ui32 index);

/**
 * @brief Sorts the list according to the provided compare function.
 * 
 * @param list The list that should be sorted.
 * @param comparer The compare function that should be used to sort the elements of the list.
 */
void flib_list_sort(flib_list *list, flib_list_compare_func comparer);

/**
 * @brief Searches for an item in the list. If the list contains the item, the index of the first occurence is returned, otherwise -1.
 * 
 * @param list The list in which the item should be searched for.
 * @param item The item that should be searched for.
 * @param out_index The index of the first occurence of the item if the item was found, otherwise -1.
 */
void flib_list_find(flib_list *list, void *item, flib_i32 *out_index);

#endif /* FLIB_LIST_H */