#ifndef PCB_H
#define PCB_H

#define MAX_DESC            8           // Max num of file descriptors is 8 per task
#define END_OF_KERNEL_PAGE  0x800000
#define PCB_PLUS_STACK      0x2000      // 8KB

#include "lib.h"
#include "file_system.h"
#include "rtc.h"
#include "terminal.h"
#include "x86_desc.h"

// sets flag field of file descriptors
typedef enum {NOT_USED, IN_USE} status_t;

/* Contains the functions that are kept in the jump table */
typedef struct f_ops_table {
    int32_t (*open)(const uint8_t* filename);
    int32_t (*read)(int32_t fd, void *buf, int32_t nbytes);
    int32_t (*write)(int32_t fd, const void *buf, int32_t nbytes);
    int32_t (*close)(int32_t fd);
} f_ops_table;

f_ops_table empty_f_ops_tab;

/* One entry in the file descriptor array, specific to each PCB */
typedef struct fdesc {
    f_ops_table* file_ops;          // pointer to file operations jump table
    uint32_t inode;                 // inode number
    uint32_t file_pos;              // current position in file
    status_t flags;                 // status of file at the moment
} fdesc_t;

// Forward declaration so that a pcb can contain another pcb
typedef struct pcb_t pcb_t;
struct pcb_t {
    fdesc_t io_files[MAX_DESC];         // file descriptor array
    uint32_t esp, ebp, esp0;
    uint32_t *page_addr;                // pointer to process's page
    pcb_t* parent_task;                 // pointer to parent task's PCB
    uint32_t fd_status;                 // bitmap of which fds are occupied
    uint8_t term_num;                   // which terminal am I on?
    uint32_t pid;                       // process id
    uint32_t pcb_num;                   // number of the pcb (1-8)
    uint8_t arg[KEY_BUF_SIZE];          // maximum possible chars (for simplicity)
    uint8_t cmd_name[33];               // name of the command (defined to be this long in execute)
};

pcb_t * init_pcb();
int32_t close_pcb(pcb_t *blk);
int32_t open_file_desc(pcb_t *blk, uint8_t *filename);
int32_t close_file_desc(pcb_t *blk, uint32_t fd_id);

uint32_t find_empty_pcb(void);
int find_empty_fd(void);
void done_with_fd(int fd);
uint32_t our_popcount(uint32_t value);

extern pcb_t *cur_pcb;
extern uint32_t pcb_status;

#endif /* PCB_H */
