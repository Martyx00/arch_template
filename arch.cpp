
#include "arch.h"
#include "binaryninjaapi.h"
#include <cstddef>
#include <vector>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "disass.h"
#include "binaryninjaapi.h"
#include "binaryninjacore.h"
#include "lowlevelilinstruction.h"
#include "binaryninjaapi.h"
#include "disass.h"

using namespace BinaryNinja;
using namespace std;

class ArchitecturePlugin : public Architecture
{
private:
	BNEndianness endian;

	/* this can maybe be moved to the API later */
	BNRegisterInfo RegisterInfo(uint32_t fullWidthReg, size_t offset, size_t size, bool zeroExtend = false)
	{
		BNRegisterInfo result;
		result.fullWidthRegister = fullWidthReg;
		result.offset = offset;
		result.size = size;
		result.extend = zeroExtend ? ZeroExtendToFullWidth : NoExtend;
		return result;
	}

public:
	/* initialization list */
	ArchitecturePlugin(const char *name) : Architecture(name)
	{
	}

	/*************************************************************************/

	std::string GetSysregName(int sysreg_id)
	{
		switch (sysreg_id)
		{
    		/*case NEC_SYSREG_EIPC:
    			return "eipc";
    		case NEC_SYSREG_EIPSW:
    			return "eipsw";*/
    		default:
    			return "INVALID";
		}
	}

	virtual BNEndianness GetEndianness() const override
	{
		return LittleEndian;
	}

	virtual size_t GetAddressSize() const override
	{
		return 4;
	}

	virtual size_t GetDefaultIntegerSize() const override
	{
		return 4;
	}

	virtual size_t GetInstructionAlignment() const override
	{
		return 2;
	}

	virtual size_t GetMaxInstructionLength() const override
	{
		return 8;
	}

	virtual vector<uint32_t> GetAllFlags() override
	{
		return vector<uint32_t>{
			//FLAG_SAT,
			};
	}

	virtual string GetFlagName(uint32_t flag) override
	{
		switch (flag)
		{
		/*case FLAG_SAT:
			return "sat";
		case FLAG_CY:
			return "cy";
		*/
		default:
			return "ERR_FLAG_NAME";
		}
	}

	virtual vector<uint32_t> GetAllFlagWriteTypes() override
	{
		return vector<uint32_t>{
			//FLAG_WRITE_NONE,
			//FLAG_WRITE_ALL,
			};
	}

	virtual string GetFlagWriteTypeName(uint32_t writeType) override
	{
		switch (writeType)
		{
    		/*case FLAG_WRITE_CYSZ:
    			return "cysz";*/

    		default:
    			return "none";
		}
	}

	virtual vector<uint32_t> GetFlagsWrittenByFlagWriteType(uint32_t writeType) override
	{
		switch (writeType)
		{
    		/*case FLAG_WRITE_CYSZ:
    			return vector<uint32_t>{
    				FLAG_CY, FLAG_Z, FLAG_S};
    		case FLAG_WRITE_SZ:
    			return vector<uint32_t>{
    				FLAG_Z, FLAG_S};*/
    		default:
    			return vector<uint32_t>();
		}
	}

	virtual BNFlagRole GetFlagRole(uint32_t flag, uint32_t semClass) override
	{

		switch (flag)
		{
    		/*case FLAG_SAT:
    			return SpecialFlagRole;*/
    		default:
    			return SpecialFlagRole;
		}
	}

	virtual vector<uint32_t> GetFlagsRequiredForFlagCondition(BNLowLevelILFlagCondition cond, uint32_t) override
	{

		switch (cond)
		{
    		/*case LLFC_E:  // Equal
    		case LLFC_NE: // Not equal
    			return vector<uint32_t>{FLAG_Z};
            */
    		default:
    			return vector<uint32_t>();
		}
	}

	virtual vector<uint32_t> GetFullWidthRegisters() override
	{

		return vector<uint32_t>{
			//NEC_REG_R0, NEC_REG_R1, NEC_REG_R2, NEC_REG_SP, NEC_REG_R4, NEC_REG_R5, NEC_REG_R6, NEC_REG_R7,
			};
	}

	virtual vector<uint32_t> GetAllRegisters() override
	{
		vector<uint32_t> result = {
			//NEC_REG_R0, NEC_REG_R1, NEC_REG_R2, NEC_REG_SP, NEC_REG_R4, NEC_REG_R5, NEC_REG_R6, NEC_REG_R7,
			};

		return result;
	}

	virtual vector<uint32_t> GetSystemRegisters() override
	{
		vector<uint32_t> result = {
			//NEC_SYSREG_EIPC,


		};

		return result;
	}

	virtual std::vector<uint32_t> GetGlobalRegisters() override
	{
		return vector<uint32_t>{
		  //NEC_REG_PC
		};
	}

	virtual string GetRegisterName(uint32_t regId) override
	{
		const char *result;

		/*if (regId >= NEC_REG_R0 && regId <= NEC_REG_PC)
			result = reg_name[regId];
		else if (regId >= NEC_SYSREG_EIPC && regId <= NEC_SYSREG_MEI)
			return GetSysregName(regId);
		else*/
			result = "";
		return result;
	}

	ExprId get_reg(LowLevelILFunction &il, int reg_id, int size) {
		if (reg_id == 0)
			return il.Const(size, 0);
		else
			return il.Register(size, reg_id);
	}

	virtual BNRegisterInfo GetRegisterInfo(uint32_t regId) override
	{
		switch (regId)
		{
    		/*case NEC_REG_R0:
    			return RegisterInfo(NEC_REG_R0, 0, 4);*/
    		default:
    			return RegisterInfo(0, 0, 0);
		}
	}

	virtual uint32_t GetStackPointerRegister() override
	{
		return NULL;
	}

	virtual uint32_t GetLinkRegister() override
	{
		return NULL;
	}


virtual std::string GetIntrinsicName (uint32_t intrinsic) override {
         switch (intrinsic)  {
            /*case SCH1L_INTRINSIC:
                return "_CountLeadingZeros";
            */
            default:
                return "";
            }
    }

    virtual std::vector<uint32_t> GetAllIntrinsics() override {
        return vector<uint32_t> {
            //SCH1L_INTRINSIC,

        };
    }

    virtual std::vector<NameAndType> GetIntrinsicInputs (uint32_t intrinsic) override {
        switch (intrinsic)
            {
                /*case SCH1L_INTRINSIC:
                    return {
                        NameAndType("WORD", Type::IntegerType(4, false))
                    };*/

                default:
                    return vector<NameAndType>();
            }
    }

    virtual std::vector<Confidence<Ref<Type>>> GetIntrinsicOutputs (uint32_t intrinsic) override {
        switch (intrinsic)
            {
                /*case SCH1L_INTRINSIC:
                    return { Type::IntegerType(4, false) };
                */
                default:
                    return vector<Confidence<Ref<Type>>>();
            }
    }

	virtual bool GetInstructionLowLevelIL(const uint8_t *data, uint64_t addr, size_t &len, LowLevelILFunction &il) override
	{

		return false;
		/*if (addr == 0x000d0d0c) {
			LogInfo("%s AT 0x%x: N: %d", insn->name, (uint32_t)addr,insn->n);
			LogInfo("%s OP[0] type: %d: value: %d", insn->name, insn->fields[0].type,insn->fields[0].value);
			LogInfo("%s OP[1] type: %d: value: %d", insn->name, insn->fields[1].type,insn->fields[1].value);
			LogInfo("%s OP[2] type: %d: value: %d", insn->name, insn->fields[2].type,insn->fields[2].value);
		}*/
	}

	virtual bool GetInstructionInfo(const uint8_t *data, uint64_t addr, size_t maxLen, InstructionInfo &result) override
	{
		return false;
	}

	virtual bool GetInstructionText(const uint8_t *data, uint64_t addr, size_t &len, std::vector<InstructionTextToken> &result) override
	{
		return false;
	}
};


// CALLING CONVENTION
class ArchCallingConvention : public CallingConvention
{
public:
	ArchCallingConvention(Architecture *arch) : CallingConvention(arch, "default")
	{
	}

	virtual vector<uint32_t> GetIntegerArgumentRegisters() override
	{
		return vector<uint32_t>{
			};
	}

	virtual uint32_t GetIntegerReturnValueRegister() override
	{
		return 0;
	}

	virtual vector<uint32_t> GetCallerSavedRegisters() override
	{
		return vector<uint32_t>{
			};
	}

	virtual vector<uint32_t> GetCalleeSavedRegisters() override
	{
		return vector<uint32_t>{
			};
	}
};

extern "C"
{
	BN_DECLARE_CORE_ABI_VERSION

	BINARYNINJAPLUGIN void CorePluginDependencies()
	{
		AddOptionalPluginDependency("view_elf");
		AddOptionalPluginDependency("view_macho");
		AddOptionalPluginDependency("view_pe");
	}

	BINARYNINJAPLUGIN bool CorePluginInit()
	{

		/* create, register arch in global list of available architectures */
		Architecture *architecture = new ArchitecturePlugin("ArchName");
		Architecture::Register(architecture);
		Ref<CallingConvention> conv;
		conv = new ArchCallingConvention(architecture);
		architecture->RegisterCallingConvention(conv);
		architecture->SetDefaultCallingConvention(conv);

		/*#define EM_NEC850 87
		BinaryViewType::RegisterArchitecture(
			"ELF",
			EM_NEC850,
			LittleEndian,
			nec850);
		#define EM_NECV850 36
		BinaryViewType::RegisterArchitecture(
			"ELF",
			EM_NECV850,
			LittleEndian,
			nec850);*/

		return true;
	}
}
