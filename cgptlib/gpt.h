/* Copyright (c) 2010 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Defines EFI related structure. See more details in EFI 2.3 spec.
 *
 * To download EFI standard, please visit UEFI homepage:
 *    http://www.uefi.org/
 */
#ifndef VBOOT_REFERENCE_CGPTLIB_GPT_H_
#define VBOOT_REFERENCE_CGPTLIB_GPT_H_

#include <stdint.h>

#define GPT_HEADER_SIGNATURE "EFI PART"
#define GPT_HEADER_SIGNATURE_SIZE sizeof(GPT_HEADER_SIGNATURE)
#define GPT_HEADER_REVISION 0x00010000

#define GPT_ENT_TYPE_EFI \
  {{Uuid: {0xc12a7328,0xf81f,0x11d2,0xba,0x4b,{0x00,0xa0,0xc9,0x3e,0xc9,0x3b}}}}
#define GPT_ENT_TYPE_UNUSED \
  {{Uuid: {0x00000000,0x0000,0x0000,0x00,0x00,{0x00,0x00,0x00,0x00,0x00,0x00}}}}
#define GPT_ENT_TYPE_CHROMEOS_KERNEL \
  {{Uuid: {0xfe3a2a5d,0x4f32,0x41a7,0xb7,0x25,{0xac,0xcc,0x32,0x85,0xa3,0x09}}}}
#define GPT_ENT_TYPE_CHROMEOS_ROOTFS \
  {{Uuid: {0x3cb8e202,0x3b7e,0x47dd,0x8a,0x3c,{0x7f,0xf2,0xa1,0x3c,0xfc,0xec}}}}
#define GPT_ENT_TYPE_CHROMEOS_RESERVED \
  {{Uuid: {0x2e0a753d,0x9e48,0x43b0,0x83,0x37,{0xb1,0x51,0x92,0xcb,0x1b,0x5e}}}}

#define UUID_NODE_LEN 6
#define GUID_SIZE 16

/*  GUID definition.
 *  Defined in appendix A of EFI standard.
 */
typedef struct {
  union {
    struct {
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_high_and_version;
      uint8_t clock_seq_high_and_reserved;
      uint8_t clock_seq_low;
      uint8_t node[UUID_NODE_LEN];
    } Uuid;
    uint8_t raw[GUID_SIZE];
  };
} __attribute__((packed)) Guid;

/* GPT header defines how many partitions exist on a drive and sectors managed.
 * For every drive device, there are 2 headers, primary and secondary.
 * Most of fields are duplicated except my_lba and entries_lba.
 *
 * You may find more details in chapter 5 of EFI standard.
 */
typedef struct {
  char signature[8];
  uint32_t revision;
  uint32_t size;
  uint32_t header_crc32;
  uint32_t reserved;
  uint64_t my_lba;
  uint64_t alternate_lba;
  uint64_t first_usable_lba;
  uint64_t last_usable_lba;
  Guid disk_uuid;

  uint64_t entries_lba;
  uint32_t number_of_entries;
  uint32_t size_of_entry;
  uint32_t entries_crc32;
  uint32_t padding;  /* since header size must be a multiple of 8, pad here. */
} GptHeader;

/* GPT partition entry defines the starting and ending LBAs of a partition.
 * It also contains the unique GUID, type, and attribute bits.
 *
 * You may find more details in chapter 5 of EFI standard.
 */
typedef struct {
  Guid type;
  Guid unique;
  uint64_t starting_lba;
  uint64_t ending_lba;
  uint64_t attributes;
  uint16_t name[36];  /* UTF-16 encoded partition name */
} GptEntry;

#endif  /* VBOOT_REFERENCE_CGPTLIB_GPT_H_ */
