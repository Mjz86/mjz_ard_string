// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct String_memory_strorage_t {
	using strize_t = uintptr_t;
	enum  class str_states_e {
		/* Stack*/
		ascii_sso = 0,
		/* Stack*/
		non_ascii_sso,
		/*ptr to heap : */
		owned_heap,
		/*ptr to constant heap : */
		sheared_heap,
		/*ptr to constant static(or   long lived obj ): */
		string_view,
		/*only for vector< string > like data structure*/
		owned_rope_str,
		/*only for constant vector< string > like data structure*/
		sheared_rope_str,
		/* Error stack type */
		error_sso_exeption,
		/* Error heap type */
		error_owned_exeption,
		/* Error constant string litteral  */
		error_string_view
	};
	enum character_encoding_standards {
		Ascii = 0,
		UTF8,
		UTF16,
		UTF32,
		resurved4,
		resurved5,
		resurved6,
		resurved7,
		resurved8,
		resurved9,
		resurved10,
		resurved11,
		resurved12,
		resurved13,
		resurved14,
		resurved15,
	};
	inline static constexpr void iam_at(str_states_e) {

	}  inline static constexpr void iam_with(character_encoding_standards) {

	}

	static_assert(sizeof(char) == 1 && sizeof(uint8_t) == 1 && 2 <= sizeof(uintptr_t) && sizeof(uintptr_t) <= 8, " this arcutecture is not supported :( ");
#define MJZ_CONSTANT(Type) \
inline static constexpr const Type 

	MJZ_CONSTANT(size_t) the_internal_ascii_capacity = sizeof(uintptr_t) * 4 - 1;
	union {
		char internal_memory_as_charater_buffer[the_internal_ascii_capacity + 1];
		uint8_t internal_memory_as_ucharater_buffer[the_internal_ascii_capacity + 1];
		uintptr_t internal_memory[4];
		struct {
			uintptr_t m_string_begin;
			uintptr_t m_length_plus_flags;
			uintptr_t m_external_data_ptr;
			union {
				uintptr_t m_capacity_plus_flags_plus_control_byte;
				struct {
					uint8_t _no_use_on_normal_just_fillers_[sizeof(uintptr_t) - 1];
					union {
						uint8_t m_control_byte;
						uint8_t m_ascii_cap_minus_len;
						char m_ascii_cap_minus_len_as_null_terminator;
					};
				};
			};
		};
	};
protected:
	String_memory_strorage_t(const String_memory_strorage_t&) = delete;
	String_memory_strorage_t& operator=(const String_memory_strorage_t&) = delete;

	constexpr inline  String_memory_strorage_t() noexcept :internal_memory{ 0,0,0,0 } {
		m_ascii_cap_minus_len = the_internal_ascii_capacity;
		iam_at(str_states_e::ascii_sso);
	};
	constexpr inline    String_memory_strorage_t(String_memory_strorage_t&&) = delete;
	constexpr inline   String_memory_strorage_t& operator=(String_memory_strorage_t&&) = delete;
	constexpr inline  ~String_memory_strorage_t()noexcept = default;

};
struct String_heap_strorage_begin_data_t {
	using strize_t = String_memory_strorage_t::strize_t;
	union { /*  an owner can think that is doesn't own until it checks the ref count;
		but a sheare holder shall know it's data is sharead  */
		std::atomic<strize_t> refrence_count_for_a_sheared_state_owner;
		std::atomic<strize_t> nessesery_refrence_count_for_sheared;
	};
	strize_t optional_hash_of_a_string_part;
};
class string_inner_ssoable_generic_exeption_t {
	using strize_t = String_memory_strorage_t::strize_t;
	inline constexpr   string_inner_ssoable_generic_exeption_t()noexcept {}
	inline virtual constexpr   ~string_inner_ssoable_generic_exeption_t()noexcept {}
	string_inner_ssoable_generic_exeption_t operator=(const string_inner_ssoable_generic_exeption_t&) = delete;
	string_inner_ssoable_generic_exeption_t operator=(string_inner_ssoable_generic_exeption_t&&) = delete;
	string_inner_ssoable_generic_exeption_t(const string_inner_ssoable_generic_exeption_t&) = delete;
	string_inner_ssoable_generic_exeption_t(string_inner_ssoable_generic_exeption_t&&) = delete;
	using str_exp_t = string_inner_ssoable_generic_exeption_t;/*
	if nullptr gets returned we may have some small exeption optimization problems
	;;
	this is just a "str_exp_t* ptr =new (destination) Type(std::move(*this));"
	*/
	virtual  str_exp_t* move_this_to_uninitilized_memory_and_get_the_new_address_back(void* destination, strize_t size_of_storage, strize_t alinemet_of_storage)noexcept = 0;
	virtual const void* get_the_real_address() const noexcept = 0;
	virtual bool has_error() const noexcept { return true; }
	virtual strize_t get_alignement_of_type()const noexcept = 0;
	virtual strize_t get_size_of_type()const noexcept = 0;
	virtual std::string_view what_exeption() noexcept { return "deafult string exeption "; };
	virtual void* user_function(void*)noexcept { return nullptr; }
	virtual void* user_function(void*) const noexcept { return nullptr; }
	virtual type_info get_type_info()const noexcept = 0;
};
enum class string_unpacker_do :int {
	const_no_change,
	unpack_non_sso,
	unpacke_all,
};
template<bool B>
struct sso_storage_if_unpack_all_t {
	char sso_data_storage[String_memory_strorage_t::the_internal_ascii_capacity + 1]{};
};
template<>
struct sso_storage_if_unpack_all_t<false> {};
struct do_none_t {};
struct Rope_memory_strorage_t;
template<bool Is_const, bool Has_temp_sso>
struct temp_string_data_storage_t :sso_storage_if_unpack_all_t <Has_temp_sso> {
	using   state_t = String_memory_strorage_t::str_states_e;
	using strize_t = String_memory_strorage_t::strize_t;
	template<typename T>
	using const_if_const = std::conditional_t< Is_const, const T, T>;
	using  flag_t = const_if_const<bool>;
	
	union {
		const_if_const<String_memory_strorage_t>* optional_optional_underlying_string{};
		const_if_const<Rope_memory_strorage_t>* optional_optional_underlying_string_vector;
	};
	union {
		const_if_const<char>* optional_string_begin{};
		const_if_const<String_memory_strorage_t>* optional_string_vector_begin;
	};
	union {
		const_if_const<strize_t> optional_string_length{};
		const_if_const<strize_t> optional_string_vector_length;
	};
	union {
		const_if_const<strize_t> optional_optional_string_capacity{};
		const_if_const<strize_t> optional_optional_string_vector_capacity;
	};
	const_if_const<String_heap_strorage_begin_data_t>* optional_heap_data{};
	const_if_const<string_inner_ssoable_generic_exeption_t>* optional_exeption{};
	const_if_const<state_t> state{};
	const_if_const< String_memory_strorage_t::character_encoding_standards>encoding{};
	flag_t has_valid_string_hash{};
	flag_t has_null_terminator{};
	bool is_a_valid_temporary{ false };
	MJZ_CONSTANT(flag_t) can_have_sso_string_in_temp = Has_temp_sso;
	MJZ_CONSTANT(flag_t) is_const = Is_const;
	inline static constexpr void iam_at(state_t) {

	}  inline static constexpr void iam_with(String_memory_strorage_t::character_encoding_standards) {

	}

};
template<bool was_const, bool Has_temp_sso>
temp_string_data_storage_t<true, Has_temp_sso> convert_to_const_temp_string_data_storage(temp_string_data_storage_t< was_const, Has_temp_sso>&& temp) {


	if constexpr (was_const) {
		temp_string_data_storage_t<true, Has_temp_sso> ret = std::move(temp);
		temp.is_a_valid_temporary = false;
		return ret;
	}
	else {
		temp_string_data_storage_t<true, Has_temp_sso> ret {
			/*
			note that the type dosen't matter in this context
			*/.optional_optional_underlying_string = temp.optional_optional_underlying_string,
			.optional_string_begin = temp.optional_string_begin,
			.optional_string_length = temp.optional_string_length,
			.optional_optional_string_capacity = temp.optional_optional_string_capacity,
			. optional_heap_data = temp. optional_heap_data,
			.optional_exeption = temp.optional_exeption,
			.state = temp.state,
			.encoding = temp.encoding,
			.has_valid_string_hash = temp.has_valid_string_hash,
			.has_null_terminator = temp.has_null_terminator,
			.is_a_valid_temporary = true};
		temp.is_a_valid_temporary = false;
		return ret;
	}
}
struct str_data_extracter {
	using state_t = String_memory_strorage_t::str_states_e;
	using encod_t = String_memory_strorage_t::character_encoding_standards;
	template<typename T>
	using not_null_t = T;
	template<bool Has_temp_sso>
	temp_string_data_storage_t<false, Has_temp_sso> extract_data(not_null_t<String_memory_strorage_t*>This) {
	
		temp_string_data_storage_t<false, Has_temp_sso>ret{.optional_optional_underlying_string = This};
		uint8_t control_byte = This->m_control_byte;
		if (control_byte & 0b11100000==0) {
			extract_data_of_ascii_sso(control_byte, *This, ret);
			return ret;
		}
		if (control_byte & 0b11111111 == 0b00100000) {
			extract_data_of_error(control_byte, *This, ret);
			return ret;
		}
		if (control_byte & 0b11110000 == 0b00100000) {
			extract_data_of_non_ascii_sso(control_byte, *This, ret);
			return ret;
		}if (control_byte & 0b11110000 == 0b00110000) {
			extract_data_of_rope_state(control_byte, *This, ret);
			return ret;
		}
		if (control_byte & 0b11000000 == 0b01000000) {
			extract_data_of_owned_string(control_byte, *This, ret);
			return ret;
		}if (control_byte & 0b11000000 == 0b10000000) {
			extract_data_of_sheared_string(control_byte, *This, ret);
			return ret;
		}if (control_byte & 0b11000000 == 0b11000000) {
			extract_data_of_string_view(control_byte, *This, ret);
			return ret;
		}
		__assume(false);
	}
private:
	template<bool Has_temp_sso>
	void extract_data_of_error(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}template<bool Has_temp_sso>
		void extract_data_of_rope_state(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}
	template<bool Has_temp_sso>
	void extract_data_of_owned_string(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}
	template<bool Has_temp_sso>
	void extract_data_of_sheared_string(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}
	template<bool Has_temp_sso>
	void extract_data_of_string_view(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}
	
	
	template<bool Has_temp_sso>
	void extract_data_of_non_ascii_sso(uint8_t control_byte, String_memory_strorage_t& Self, temp_string_data_storage_t<false, Has_temp_sso>& ret) {
	}
	template<bool Has_temp_sso>
	void extract_data_of_ascii_sso(uint8_t control_byte, String_memory_strorage_t&Self, temp_string_data_storage_t<false, Has_temp_sso>&ret) {
		ret.state = state_t::ascii_sso;
		ret.encoding = encod_t::Ascii;
		ret.has_null_terminator = true;
		ret.has_valid_string_hash = false;
		ret.optional_optional_string_capacity = Self.the_internal_ascii_capacity;
		ret.optional_string_length = ret.optional_optional_string_capacity - control_byte;
		if constexpr (Has_temp_sso) {
			std::memcpy(ret.sso_data_storage, Self.internal_memory_as_charater_buffer, ret.optional_string_length);
			ret.optional_string_begin = ret.sso_data_storage;
		}
		else {
			ret.optional_string_begin = Self.internal_memory_as_charater_buffer;
		}
		ret.is_a_valid_temporary = true;
		Self.iam_at(state_t::ascii_sso);
		ret.iam_at(state_t::ascii_sso);
	}
};




/*
not rope for the moment
*/
template<string_unpacker_do do_what_T>
struct String_memory_unpacked_t :temp_string_data_storage_t< string_unpacker_do::const_no_change == do_what_T, do_what_T == string_unpacker_do::unpacke_all> {
	String_memory_unpacked_t(const String_memory_unpacked_t&) = delete;
	String_memory_unpacked_t(String_memory_unpacked_t&&) = delete;
	String_memory_unpacked_t operator=(const String_memory_unpacked_t&) = delete;
	String_memory_unpacked_t operator=(String_memory_unpacked_t&&) = delete;
	constexpr inline  String_memory_unpacked_t(do_none_t)noexcept {}
	constexpr inline   String_memory_unpacked_t()noexcept {}
	constexpr inline   ~String_memory_unpacked_t()noexcept {}

};
int main()
{
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
