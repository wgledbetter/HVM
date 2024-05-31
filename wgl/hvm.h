#pragma once

// Header interface for hvm.c

// #include <dlfcn.h>
#include <inttypes.h>
#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Integers --------------------------------------------------------------------

typedef uint8_t bool;

typedef uint8_t u8;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef uint64_t u64;

typedef _Atomic(u8) a8;
typedef _Atomic(u16) a16;
typedef _Atomic(u32) a32;
typedef _Atomic(u64) a64;

// Configuration ---------------------------------------------------------------

// Threads per CPU
#ifndef TPC_L2
  #define TPC_L2 0
#endif
#define TPC (1ul << TPC_L2)

// Types -----------------------------------------------------------------------

// Local Types
typedef u8 Tag;    // Tag  ::= 3-bit (rounded up to u8)
typedef u32 Val;   // Val  ::= 29-bit (rounded up to u32)
typedef u32 Port;  // Port ::= Tag + Val (fits a u32)
typedef u64 Pair;  // Pair ::= Port + Port (fits a u64)

typedef a32 APort;  // atomic Port
typedef a64 APair;  // atomic Pair

// Rules
typedef u8 Rule;  // Rule ::= 3-bit (rounded up to 8)

// Numbs
typedef u32 Numb;  // Numb ::= 29-bit (rounded up to u32)

// Tags
#define VAR 0x0  // variable
#define REF 0x1  // reference
#define ERA 0x2  // eraser
#define NUM 0x3  // number
#define CON 0x4  // constructor
#define DUP 0x5  // duplicator
#define OPR 0x6  // operator
#define SWI 0x7  // switch

// Interaction Rule Values
#define LINK 0x0
#define CALL 0x1
#define VOID 0x2
#define ERAS 0x3
#define ANNI 0x4
#define COMM 0x5
#define OPER 0x6
#define SWIT 0x7

// Numbers
#define TY_SYM 0x00
#define TY_U24 0x01
#define TY_I24 0x02
#define TY_F24 0x03
#define OP_ADD 0x04
#define OP_SUB 0x05
#define FP_SUB 0x06
#define OP_MUL 0x07
#define OP_DIV 0x08
#define FP_DIV 0x09
#define OP_REM 0x0A
#define FP_REM 0x0B
#define OP_EQ  0x0C
#define OP_NEQ 0x0D
#define OP_LT  0x0E
#define OP_GT  0x0F
#define OP_AND 0x10
#define OP_OR  0x11
#define OP_XOR 0x12
#define OP_SHL 0x13
#define FP_SHL 0x14
#define OP_SHR 0x15
#define FP_SHR 0x16

// Constants
#define FREE 0x00000000
#define ROOT 0xFFFFFFF8
#define NONE 0xFFFFFFFF

// Cache Padding
#define CACHE_PAD 64

// Global Net
#define HLEN       (1ul << 16)  // max 16k high-priority redexes
#define RLEN       (1ul << 24)  // max 16m low-priority redexes
#define G_NODE_LEN (1ul << 29)  // max 536m nodes
#define G_VARS_LEN (1ul << 29)  // max 536m vars
#define G_RBAG_LEN (TPC * RLEN)

typedef struct Net {
  APair node_buf[G_NODE_LEN];  // global node buffer
  APort vars_buf[G_VARS_LEN];  // global vars buffer
  APair rbag_buf[G_RBAG_LEN];  // global rbag buffer
  a64 itrs;                    // interaction count
  a32 idle;                    // idle thread counter
} Net;

// Top-Level Definition
typedef struct Def {
  char name[256];
  bool safe;
  u32 rbag_len;
  u32 node_len;
  u32 vars_len;
  Port root;
  Pair rbag_buf[0xFFF];
  Pair node_buf[0xFFF];
} Def;

typedef struct Book Book;

// A Foreign Function
typedef struct {
  char name[256];
  Port (*func)(Net*, Book*, Port);
} FFn;

// Book of Definitions
typedef struct Book {
  u32 defs_len;
  Def defs_buf[0x4000];
  u32 ffns_len;
  FFn ffns_buf[0x4000];
} Book;

// Local Thread Memory
typedef struct TM {
  u32 tid;              // thread id
  u32 itrs;             // interaction count
  u32 nput;             // next node allocation attempt index
  u32 vput;             // next vars allocation attempt index
  u32 hput;             // next hbag push index
  u32 rput;             // next rbag push index
  u32 sidx;             // steal index
  u32 nloc[0xFFF];      // node allocation indices
  u32 vloc[0xFFF];      // vars allocation indices
  Pair hbag_buf[HLEN];  // high-priority redexes
} TM;

// Readback: λ-Encoded Ctr
typedef struct Ctr {
  u32 tag;
  u32 args_len;
  Port args_buf[16];
} Ctr;

// Readback: λ-Encoded Str (UTF-32)
// FIXME: this is actually ASCII :|
// FIXME: remove len limit
typedef struct Str {
  u32 text_len;
  char text_buf[256];
} Str;

// IO Magic Number
#define IO_MAGIC_0 0xD0CA11
#define IO_MAGIC_1 0xFF1FF1

// IO Tags
#define IO_DONE 0
#define IO_CALL 1

// List Type
#define LIST_NIL  0
#define LIST_CONS 1

// Booleans
#define TRUE  1
#define FALSE 0

// Main ------------------------------------------------------------------------

void hvm_c(u32* book_buffer);
