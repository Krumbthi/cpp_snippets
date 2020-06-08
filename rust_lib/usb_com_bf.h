extern "C" {

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint16_t majorRelease;
  uint16_t minorRelease;
  uint16_t patchLevel;
  uint16_t build;
} Version;

uint32_t USBCO_CloseDLL(void);

uint32_t USBCO_GetOpticSN(uint32_t *serial_no);

uint32_t USBCO_InitDLL(Version *dll_version);

void USBCO_InitDLL_free(Version *ptr);

uint32_t USBRO18_ReadOutput(uint16_t *i_mask);

}