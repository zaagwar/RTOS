#ifndef RP2040_MAILBOX_H
#define RP2040_MAILBOX_H

#include <rp2040/common.h>

bool     Mailbox_Is_Empty  (void);
bool     Mailbox_Is_Full   (void);
void     Write_To_Mailbox  (uint32_t Data);
uint32_t Read_From_Mailbox (void);

#endif /* RP2040_MAILBOX_H */
