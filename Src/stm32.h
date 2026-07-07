
#ifndef STM32F407_MIN_H
#define STM32F407_MIN_H

#include <stdint.h>

/* ============================================================
 * TEMEL BELLEK HARITASI (RM0090 - Memory Map tablosu)
 * ============================================================ */
#define PERIPH_BASE            (0x40000000UL)
#define AHB1PERIPH_BASE         (PERIPH_BASE + 0x00020000UL)

/* ============================================================
 * RCC (Reset and Clock Control)
 * ============================================================ */
#define RCC_BASE                (AHB1PERIPH_BASE + 0x3800UL)

typedef struct
{
  volatile uint32_t CR;            /* offset 0x00 */
  volatile uint32_t PLLCFGR;       /* offset 0x04 */
  volatile uint32_t CFGR;          /* offset 0x08 */
  volatile uint32_t CIR;           /* offset 0x0C */
  volatile uint32_t AHB1RSTR;      /* offset 0x10 */
  volatile uint32_t AHB2RSTR;      /* offset 0x14 */
  volatile uint32_t AHB3RSTR;      /* offset 0x18 */
  uint32_t          RESERVED0;     /* offset 0x1C (kullanilmiyor, bosluk) */
  volatile uint32_t APB1RSTR;      /* offset 0x20 */
  volatile uint32_t APB2RSTR;      /* offset 0x24 */
  uint32_t          RESERVED1[2];  /* offset 0x28-0x2C (bosluk) */
  volatile uint32_t AHB1ENR;       /* offset 0x30  <-- LED icin bize lazim */
  volatile uint32_t AHB2ENR;       /* offset 0x34 */
  volatile uint32_t AHB3ENR;       /* offset 0x38 */
  uint32_t          RESERVED2;     /* offset 0x3C */
  volatile uint32_t APB1ENR;       /* offset 0x40 */
  volatile uint32_t APB2ENR;       /* offset 0x44 */
} RCC_TypeDef;

#define RCC   ((RCC_TypeDef *) RCC_BASE)

/* RCC_AHB1ENR icindeki bitler -- hangi GPIO'nun saatini actigini gosterir */
#define RCC_AHB1ENR_GPIOAEN     (1UL << 0) /* push button */
#define RCC_AHB1ENR_GPIOBEN     (1UL << 1)
#define RCC_AHB1ENR_GPIOCEN     (1UL << 2)
#define RCC_AHB1ENR_GPIODEN     (1UL << 3)   /* bizim LED'imiz PD12'de */
#define RCC_AHB1ENR_GPIOEEN     (1UL << 4)

/* ============================================================
 * GPIO (General Purpose Input/Output)
 * ============================================================ */
#define GPIOA_BASE   (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE   (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE   (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE   (AHB1PERIPH_BASE + 0x0C00UL)   /* LED'imiz burada */
#define GPIOE_BASE   (AHB1PERIPH_BASE + 0x1000UL)

typedef struct
{
  volatile uint32_t MODER;     /* offset 0x00 - pin modu (input/output/AF/analog) */
  volatile uint32_t OTYPER;    /* offset 0x04 - push-pull / open-drain */
  volatile uint32_t OSPEEDR;   /* offset 0x08 - pin hizi */
  volatile uint32_t PUPDR;     /* offset 0x0C - pull-up/pull-down */
  volatile uint32_t IDR;       /* offset 0x10 - pin girisini OKUMA */
  volatile uint32_t ODR;       /* offset 0x14 - pine YAZMA (LED'i biz bununla yakiyoruz) */
  volatile uint32_t BSRR;      /* offset 0x18 - atomik set/reset (ileride bakariz) */
  volatile uint32_t LCKR;      /* offset 0x1C - pin kilitleme */
  volatile uint32_t AFR[2];    /* offset 0x20-0x24 - alternatif fonksiyon secimi */
} GPIO_TypeDef;

#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC   ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD   ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE   ((GPIO_TypeDef *) GPIOE_BASE)

#endif /* STM32F407_MIN_H */
