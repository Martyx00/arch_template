#include <inttypes.h>

#ifdef __cplusplus
  extern "C" {
#endif

enum sign {
  UNSIGNED,
  SIGNED
};

enum op_type {
    OP_REG,
    OP_MEM,
    OP_CONST
};

enum op_condition {
    NOT_EQUAL
};

enum insn_id {
    ARCH_NOP,
};

enum insn_type {
    INSN_NOP
};

typedef struct {
  int64_t value;
  uint64_t size;
  enum sign sign;
  enum op_type type;
} insn_op_t;

typedef struct {
  const char* name;
  enum insn_id insn_id;
  insn_op_t fields[10];
  uint16_t n;
  uint16_t size;
  enum insn_type op_type;
  enum op_condition cond;
} insn_t;

insn_t *disassemble(const uint8_t *in_buffer);

#ifdef __cplusplus
}
#endif
