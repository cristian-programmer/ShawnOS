#pragma once

#include <stdint.h>
#include <stddef.h>

#include <kernel/bitset.h>

#define BLOCK_SIZE_DEFAULT 0x10000 // Each heap entry (block) is 0x10000 bytes
#define SECTION_SIZE_DEFAULT 0x10  // Each block is sectioned into 16byte chunks

#define BLOCK_MAGIC 0xDEADBEEF

// KHEAP FLAGS
#define KHEAP_ALIGN (1<<0)       // All allocations are section-size aligned
#define KHEAP_AUTO_EXPAND (1<<1) // The heap will be automatically expanded as needed

/**
 * Struct placed at the beginning of each heap block
 * Serves as a link list of blocks
 */
struct kheap_block {
    uint32_t magic;
    struct kheap_block *next;
    size_t block_size;
    uint32_t section_size;

    // Total number of free sections
    size_t free_sections;
    
    uintptr_t start;
    /**
     * Bitset containing the free/allocated status of each section in the block
     */
    bitset_t used_sections;
    /**
     * Bitset containing delimiter information for each section in the block
     * A section is marked as a delimiter if it is the first or last section in an
     * allocation that has not yet been freed.
     */
    bitset_t delimiters;
};
typedef struct kheap_block kheap_block_t;

/**
 * Struct for storing heap metadata
 * Acted upon by all kheap functions
 */
struct kheap {
    kheap_block_t *first; // First block in kernel heap
                          // new blocks will go here
    uint32_t default_section_size;
    uint32_t flags;
    size_t effective_size; // Total effective size of heap (not including metadata)
    size_t max_expand_size; // Maximum size heap can be expanded at once
    size_t cur_expand_size; // Current size to expand the heap by
};
typedef struct kheap kheap_t;


extern kheap_t kheap_default;
extern kheap_t kheap_critical;

void kheap_init(kheap_t *heap, uint32_t default_section_size, uint32_t flags, size_t max_expand_size);
void kheap_kalloc_install();
k_return_t kheap_expand(kheap_t *heap, size_t size);
void kheap_add_block(kheap_t *heap, uintptr_t addr, uint32_t block_size,
                     uint32_t section_size);
uintptr_t __kheap_kalloc_malloc_real(size_t size, uintptr_t *phys, uint32_t flags);
void __kheap_kalloc_free(uintptr_t addr);
uintptr_t kheap_malloc(kheap_t *heap, size_t size, size_t align, uint32_t flags);
bool kheap_free(kheap_t *heap, uintptr_t addr);
