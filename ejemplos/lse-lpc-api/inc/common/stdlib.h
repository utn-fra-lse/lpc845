#ifndef _LSE_STDLIB_H_
#define _LSE_STDLIB_H_

#ifdef __LPC84X__
#include "lpc845/fsl_common.h"
#include "lpc845/system_LPC845.h"
#endif

// Prototipos

void sleep_ms(uint32_t ms);

/**
 * @brief Inicializacion basica
 */
static inline void stdio_init_all(void) {
	// Inicia el microcontrolador a 12MHz
	SystemCoreClockUpdate();
}

#endif
