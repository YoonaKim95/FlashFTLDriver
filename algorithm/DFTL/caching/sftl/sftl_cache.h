#ifndef __SFTL_CACHE_HEADER__
#define __SFTL_CACHE_HEADER__
#include "../../my_cache.h"
#include "../../../../include/data_struct/lru_list.h"
#include "../../../../include/data_struct/bitmap.h"

#define BITMAPFROMLN(ln) (((sftl_cache*)((ln)->data))->map)
#define HEADARRFROMLN(ln) (((sftl_cache*)((ln)->data))->head_array)
#define BITMAPMEMBER (PAGESIZE/sizeof(DMF))
#define BITMAPSIZE (BITMAPMEMBER/8+(BITMAPMEMBER%8?1:0))

#define GETOFFSET(lba) TRANSOFFSET(lba)

typedef struct sftl_cache{
	uint32_t *head_array;
	bitmap *map;
	GTD_entry *etr;
}sftl_cache;

typedef struct sftl_cache_monitor{
	uint32_t max_caching_byte;
	uint32_t now_caching_byte;
	uint32_t *gtd_size;
	LRU *lru;
}sftl_cache_monitor;

uint32_t sftl_init(struct my_cache *, uint32_t total_caching_physical_pages);
uint32_t sftl_free(struct my_cache *);
bool sftl_is_needed_eviction(struct my_cache *, uint32_t lba);
bool sftl_need_more_eviction(struct my_cache *, uint32_t lba);
uint32_t sftl_update_entry(struct my_cache *, GTD_entry *, uint32_t lba, uint32_t ppa);
uint32_t sftl_update_entry_gc(struct my_cache *, GTD_entry *, uint32_t lba, uint32_t ppa);
uint32_t sftl_insert_entry_from_translation(struct my_cache *, GTD_entry *, uint32_t lba, char *data);
uint32_t sftl_update_from_translation_gc(struct my_cache *, char *data, uint32_t lba, uint32_t ppa);
uint32_t sftl_get_mapping(struct my_cache *, uint32_t lba);
struct GTD_entry *sftl_get_eviction_GTD_entry(struct my_cache *);//if return value is NULL, it is clean eviction.
bool sftl_update_eviction_target_translation(struct my_cache* , GTD_entry *etr, mapping_entry * map, char *data);
bool sftl_exist(struct my_cache *, uint32_t lba);
#endif