/**
 * Testcases for cpputils/cpputilsshared/string_utils.h
 * @author Copyright (c) 2001 - 2023 Martin Oberzalek
 */
#include "test_string_utils.h"
#include "test_cyclicarray.h"
#include "test_static_vector.h"
#include "test_static_list.h"
#include "test_static_string.h"
#include "test_span_vector.h"
#include "ColoredOutput.h"
#include "ColBuilder.h"
#include <arg.h>
#include <iostream>
#include <OutDebug.h>
#include <memory>
#include <format.h>

using namespace Tools;

int main( int argc, char **argv )
{
	//std::cout << std::string('0', 20 ) << std::endl;

	ColoredOutput co;

	Arg::Arg arg( argc, argv );
	arg.addPrefix( "-" );
	arg.addPrefix( "--" );

	Arg::OptionChain oc_info;
	arg.addChainR(&oc_info);
	oc_info.setMinMatch(1);
	oc_info.setContinueOnMatch( false );
	oc_info.setContinueOnFail( true );

	Arg::FlagOption o_help( "help" );
	o_help.setDescription( "Show this page" );
	oc_info.addOptionR( &o_help );

	Arg::FlagOption o_debug("d");
	o_debug.addName( "debug" );
	o_debug.setDescription("print debugging messages");
	o_debug.setRequired(false);
	arg.addOptionR( &o_debug );

	if( !arg.parse() )
	{
		std::cout << arg.getHelp(5,20,30, 80 ) << std::endl;
		return 1;
	}

	if( o_debug.getState() )
	{
		Tools::x_debug = new OutDebug();
	}

	if( o_help.getState() ) {
		std::cout << arg.getHelp(5,20,30, 80 ) << std::endl;
		return 1;
	}

#if __cpp_exceptions > 0
	try {
#endif

		std::vector<std::shared_ptr<TestCaseBase<bool>>> test_cases;
/*
		test_cases.push_back( test_case_toupper1() );
		test_cases.push_back( test_case_toupper2() );
		test_cases.push_back( test_case_toupper3() );
		test_cases.push_back( test_case_toupper4() );

		test_cases.push_back( test_case_tolower1() );
		test_cases.push_back( test_case_tolower2() );
		test_cases.push_back( test_case_tolower3() );
		test_cases.push_back( test_case_tolower4() );

		test_cases.push_back( test_case_strip1() );
		test_cases.push_back( test_case_strip2() );
		test_cases.push_back( test_case_strip3() );
		test_cases.push_back( test_case_strip4() );
		test_cases.push_back( test_case_strip5() );
		test_cases.push_back( test_case_strip6() );
		test_cases.push_back( test_case_strip7() );
		test_cases.push_back( test_case_strip8() );
		test_cases.push_back( test_case_strip9() );
		test_cases.push_back( test_case_strip10() );
		test_cases.push_back( test_case_strip11() );
		test_cases.push_back( test_case_strip12() );
		test_cases.push_back( test_case_strip13() );
		test_cases.push_back( test_case_strip14() );

		test_cases.push_back( test_case_strip_view1() );
		test_cases.push_back( test_case_strip_view2() );
		test_cases.push_back( test_case_strip_view3() );
		test_cases.push_back( test_case_strip_view4() );
		test_cases.push_back( test_case_strip_view5() );
		test_cases.push_back( test_case_strip_view6() );
		test_cases.push_back( test_case_strip_view7() );
		test_cases.push_back( test_case_strip_view8() );
		test_cases.push_back( test_case_strip_view9() );
		test_cases.push_back( test_case_strip_view10() );
		test_cases.push_back( test_case_strip_view11() );
		test_cases.push_back( test_case_strip_view12() );
		test_cases.push_back( test_case_strip_view13() );
		test_cases.push_back( test_case_strip_view14() );

		test_cases.push_back( test_case_strip_leading1() );
		test_cases.push_back( test_case_strip_leading2() );
		test_cases.push_back( test_case_strip_leading3() );
		test_cases.push_back( test_case_strip_leading4() );
		test_cases.push_back( test_case_strip_leading5() );
		test_cases.push_back( test_case_strip_leading6() );
		test_cases.push_back( test_case_strip_leading7() );
		test_cases.push_back( test_case_strip_leading8() );
		test_cases.push_back( test_case_strip_leading9() );
		test_cases.push_back( test_case_strip_leading10() );
		test_cases.push_back( test_case_strip_leading11() );
		test_cases.push_back( test_case_strip_leading12() );
		test_cases.push_back( test_case_strip_leading13() );
		test_cases.push_back( test_case_strip_leading14() );

		test_cases.push_back( test_case_strip_trailing1() );
		test_cases.push_back( test_case_strip_trailing2() );
		test_cases.push_back( test_case_strip_trailing3() );
		test_cases.push_back( test_case_strip_trailing4() );
		test_cases.push_back( test_case_strip_trailing5() );
		test_cases.push_back( test_case_strip_trailing6() );
		test_cases.push_back( test_case_strip_trailing7() );
		test_cases.push_back( test_case_strip_trailing8() );
		test_cases.push_back( test_case_strip_trailing9() );
		test_cases.push_back( test_case_strip_trailing10() );
		test_cases.push_back( test_case_strip_trailing11() );
		test_cases.push_back( test_case_strip_trailing12() );
		test_cases.push_back( test_case_strip_trailing13() );
		test_cases.push_back( test_case_strip_trailing14() );

		test_cases.push_back( test_case_is_int1() );
		test_cases.push_back( test_case_is_int2() );
		test_cases.push_back( test_case_is_int3() );
		test_cases.push_back( test_case_is_int4() );
		test_cases.push_back( test_case_is_int5() );
		test_cases.push_back( test_case_is_int6() );


		test_cases.push_back( test_case_init_cyclic_array1() );
		test_cases.push_back( test_case_init_cyclic_array2() );
		test_cases.push_back( test_case_init_cyclic_array3() );
		test_cases.push_back( test_case_init_cyclic_array4() );
		test_cases.push_back( test_case_init_cyclic_array5() );

		test_cases.push_back( test_case_modify_cyclic_array1() );
		test_cases.push_back( test_case_modify_cyclic_array2() );
		test_cases.push_back( test_case_reverse_iterator() );

		test_cases.push_back( test_case_insert1() );

		test_cases.push_back( test_case_insert2() );

		test_cases.push_back( test_case_insert3() );
		test_cases.push_back( test_case_insert4() );

		test_cases.push_back( test_case_insert5() );


		test_cases.push_back( test_case_init_static_vector1() );
		test_cases.push_back( test_case_init_static_vector2() );
		test_cases.push_back( test_case_init_static_vector3() );
		test_cases.push_back( test_case_init_static_vector4() );
		test_cases.push_back( test_case_init_static_vector5() );

		test_cases.push_back( test_case_modify_static_vector1() );
		test_cases.push_back( test_case_modify_static_vector2() );
		test_cases.push_back( test_case_static_vector_reverse_iterator() );
		test_cases.push_back( test_case_static_vector_insert1() );

		test_cases.push_back( test_case_static_vector_insert2() );
		test_cases.push_back( test_case_static_vector_insert3() );
		test_cases.push_back( test_case_static_vector_insert4() );
		test_cases.push_back( test_case_static_vector_insert5() );
		test_cases.push_back( test_case_static_vector_insert6() );
		test_cases.push_back( test_case_static_vector_insert7() );
		test_cases.push_back( test_case_static_vector_insert8() );
		test_cases.push_back( test_case_static_vector_insert9() );



		test_cases.push_back( test_case_init_static_list1() );

		test_cases.push_back( test_case_init_static_list2() );
		test_cases.push_back( test_case_init_static_list3() );
		test_cases.push_back( test_case_init_static_list4() );
		test_cases.push_back( test_case_init_static_list5() );
		test_cases.push_back( test_case_init_static_list6() );
		test_cases.push_back( test_case_init_static_list7() );
		test_cases.push_back( test_case_init_static_list8() );
		test_cases.push_back( test_case_init_static_list9() );
		test_cases.push_back( test_case_init_static_list10() );
		test_cases.push_back( test_case_init_static_list11() );


		test_cases.push_back( test_case_modify_static_list1() );
		test_cases.push_back( test_case_modify_static_list2() );
		test_cases.push_back( test_case_modify_static_list3() );

		test_cases.push_back( test_case_modify_static_list4() );
		test_cases.push_back( test_case_modify_static_list5() );
		test_cases.push_back( test_case_modify_static_list6() );

		test_cases.push_back( test_case_static_list_reverse_iterator1() );
		test_cases.push_back( test_case_static_list_reverse_iterator2() );
		test_cases.push_back( test_case_static_list_reverse_iterator3() );

		test_cases.push_back( test_case_static_list_insert1() );

		test_cases.push_back( test_case_static_list_insert2() );
		test_cases.push_back( test_case_static_list_insert3() );
		test_cases.push_back( test_case_static_list_insert4() );

		test_cases.push_back( test_case_static_list_insert5() );

		test_cases.push_back( test_case_static_list_insert6() );
		test_cases.push_back( test_case_static_list_insert7() );
		test_cases.push_back( test_case_static_list_insert8() );
		test_cases.push_back( test_case_static_list_insert9() );
		test_cases.push_back( test_case_static_list_insert10() );

		test_cases.push_back( test_case_static_list_insert11() );

		test_cases.push_back( test_case_static_list_insert12() );

		test_cases.push_back( test_case_static_list_insert13() );
		test_cases.push_back( test_case_static_list_insert14() );
		test_cases.push_back( test_case_static_list_insert15() );
		test_cases.push_back( test_case_static_list_insert16() );

		test_cases.push_back( test_case_static_list_front1() );
		test_cases.push_back( test_case_static_list_front2() );

		test_cases.push_back( test_case_static_list_back1() );
		test_cases.push_back( test_case_static_list_back2() );

		test_cases.push_back( test_case_static_list_emplace1() );
		test_cases.push_back( test_case_static_list_emplace2() );

		test_cases.push_back( test_case_static_list_push_front1() );

		test_cases.push_back( test_case_static_list_reverse1() );

		test_cases.push_back( test_case_static_list_remove1() );
		test_cases.push_back( test_case_static_list_remove2() );

		test_cases.push_back( test_case_static_list_sort1() );
		test_cases.push_back( test_case_static_list_sort2() );

		test_cases.push_back( test_case_static_list_unique1() );
		test_cases.push_back( test_case_static_list_unique2() );

		test_cases.push_back( test_case_static_list_swap1() );
		test_cases.push_back( test_case_static_list_swap2() );
		test_cases.push_back( test_case_static_list_swap3() );
		test_cases.push_back( test_case_static_list_swap4() );

		test_cases.push_back( test_case_modify_static_string1() );
		test_cases.push_back( test_case_modify_static_string2() );
		test_cases.push_back( test_case_modify_static_string3() );
		test_cases.push_back( test_case_modify_static_string4() );
		test_cases.push_back( test_case_modify_static_string5() );
		test_cases.push_back( test_case_modify_static_string6() );
		test_cases.push_back( test_case_modify_static_string7() );
		test_cases.push_back( test_case_modify_static_string8() );

		test_cases.push_back( test_case_modify_static_string_replace_1() );
		test_cases.push_back( test_case_modify_static_string_replace_2() );

		test_cases.push_back( test_case_static_string_at_1() );
		test_cases.push_back( test_case_static_string_at_2() );
		test_cases.push_back( test_case_static_string_at_3() );

		test_cases.push_back( test_case_static_string_operator_at_1() );
		test_cases.push_back( test_case_static_string_operator_at_2() );
		test_cases.push_back( test_case_static_string_operator_at_3() );

		test_cases.push_back( test_case_static_string_front_1() );
		test_cases.push_back( test_case_static_string_front_2() );

		test_cases.push_back( test_case_static_string_back_1() );
		test_cases.push_back( test_case_static_string_back_2() );

		test_cases.push_back( test_case_static_string_operator_string_view_1() );

		test_cases.push_back( test_case_static_string_iterator_1() );
		test_cases.push_back( test_case_static_string_iterator_2() );
		test_cases.push_back( test_case_static_string_iterator_3() );
		test_cases.push_back( test_case_static_string_iterator_4() );

		test_cases.push_back( test_case_static_string_empty_1() );

		test_cases.push_back( test_case_static_string_size_1() );

		test_cases.push_back( test_case_static_string_length_1() );

		test_cases.push_back( test_case_static_string_shrink_to_fit_1() );

		test_cases.push_back( test_case_static_string_clear_1() );

		test_cases.push_back( test_case_static_string_insert_1() );
		test_cases.push_back( test_case_static_string_insert_2() );

		test_cases.push_back( test_case_static_string_insert_3() );

		test_cases.push_back( test_case_static_string_insert_4() );
		test_cases.push_back( test_case_static_string_insert_41() );
		test_cases.push_back( test_case_static_string_insert_42() );
		test_cases.push_back( test_case_static_string_insert_5() );

		test_cases.push_back( test_case_static_string_insert_51() );
		test_cases.push_back( test_case_static_string_insert_52() );

		test_cases.push_back( test_case_static_string_insert_6() );
		test_cases.push_back( test_case_static_string_insert_61() );
		test_cases.push_back( test_case_static_string_insert_62() );

		test_cases.push_back( test_case_static_string_insert_7() );
		test_cases.push_back( test_case_static_string_insert_71() );

		test_cases.push_back( test_case_static_string_insert_8() );
		test_cases.push_back( test_case_static_string_insert_81() );
		test_cases.push_back( test_case_static_string_insert_82() );
		test_cases.push_back( test_case_static_string_insert_83() );
		test_cases.push_back( test_case_static_string_insert_84() );

		test_cases.push_back( test_case_static_string_insert_9() );
		test_cases.push_back( test_case_static_string_insert_91() );
		test_cases.push_back( test_case_static_string_insert_92() );

		test_cases.push_back( test_case_static_string_insert_10() );
		test_cases.push_back( test_case_static_string_insert_101() );
		test_cases.push_back( test_case_static_string_insert_102() );
		test_cases.push_back( test_case_static_string_insert_103() );

		test_cases.push_back( test_case_static_string_insert_11() );
		test_cases.push_back( test_case_static_string_insert_111() );
		test_cases.push_back( test_case_static_string_insert_112() );
		test_cases.push_back( test_case_static_string_insert_113() );

		test_cases.push_back( test_case_static_string_insert_12() );
		test_cases.push_back( test_case_static_string_insert_121() );
		test_cases.push_back( test_case_static_string_insert_122() );
		test_cases.push_back( test_case_static_string_insert_123() );

		test_cases.push_back( test_case_static_string_insert_13() );
		test_cases.push_back( test_case_static_string_insert_131() );
		test_cases.push_back( test_case_static_string_insert_132() );
		test_cases.push_back( test_case_static_string_insert_133() );

		test_cases.push_back( test_case_static_string_insert_14() );
		test_cases.push_back( test_case_static_string_insert_141() );
		test_cases.push_back( test_case_static_string_insert_142() );
		test_cases.push_back( test_case_static_string_insert_143() );

		test_cases.push_back( test_case_static_string_insert_15() );
		test_cases.push_back( test_case_static_string_insert_151() );
		test_cases.push_back( test_case_static_string_insert_152() );
		test_cases.push_back( test_case_static_string_insert_153() );
		test_cases.push_back( test_case_static_string_insert_154() );

		test_cases.push_back( test_case_static_string_erase_11() );
		test_cases.push_back( test_case_static_string_erase_12() );
		test_cases.push_back( test_case_static_string_erase_13() );

		test_cases.push_back( test_case_static_string_erase_21() );
		test_cases.push_back( test_case_static_string_erase_22() );
		test_cases.push_back( test_case_static_string_erase_23() );

		test_cases.push_back( test_case_static_string_erase_31() );
		test_cases.push_back( test_case_static_string_erase_32() );
		test_cases.push_back( test_case_static_string_erase_33() );

		test_cases.push_back( test_case_static_string_push_back_1() );
		test_cases.push_back( test_case_static_string_push_back_2() );
		test_cases.push_back( test_case_static_string_push_back_3() );

		test_cases.push_back( test_case_static_string_pop_back_1() );

		test_cases.push_back( test_case_static_string_append_11() );
		test_cases.push_back( test_case_static_string_append_12() );
		test_cases.push_back( test_case_static_string_append_13() );

		test_cases.push_back( test_case_static_string_append_21() );
		test_cases.push_back( test_case_static_string_append_22() );
		test_cases.push_back( test_case_static_string_append_23() );
		test_cases.push_back( test_case_static_string_append_24() );

		test_cases.push_back( test_case_static_string_append_31() );
		test_cases.push_back( test_case_static_string_append_32() );
		test_cases.push_back( test_case_static_string_append_33() );

		test_cases.push_back( test_case_static_string_append_41() );
		test_cases.push_back( test_case_static_string_append_42() );
		test_cases.push_back( test_case_static_string_append_43() );
		test_cases.push_back( test_case_static_string_append_44() );

		test_cases.push_back( test_case_static_string_append_51() );
		test_cases.push_back( test_case_static_string_append_52() );
		test_cases.push_back( test_case_static_string_append_53() );
		test_cases.push_back( test_case_static_string_append_54() );

		test_cases.push_back( test_case_static_string_append_61() );
		test_cases.push_back( test_case_static_string_append_62() );
		test_cases.push_back( test_case_static_string_append_63() );
		test_cases.push_back( test_case_static_string_append_64() );

		test_cases.push_back( test_case_static_string_append_71() );
		test_cases.push_back( test_case_static_string_append_72() );
		test_cases.push_back( test_case_static_string_append_73() );
		test_cases.push_back( test_case_static_string_append_74() );

		test_cases.push_back( test_case_static_string_append_81() );
		test_cases.push_back( test_case_static_string_append_82() );
		test_cases.push_back( test_case_static_string_append_83() );
		test_cases.push_back( test_case_static_string_append_84() );

		test_cases.push_back( test_case_static_string_append_91() );
		test_cases.push_back( test_case_static_string_append_92() );
		test_cases.push_back( test_case_static_string_append_93() );
		test_cases.push_back( test_case_static_string_append_94() );

		test_cases.push_back( test_case_static_string_append_101() );
		test_cases.push_back( test_case_static_string_append_102() );
		test_cases.push_back( test_case_static_string_append_103() );
		test_cases.push_back( test_case_static_string_append_104() );

		test_cases.push_back( test_case_static_string_append_111() );
		test_cases.push_back( test_case_static_string_append_112() );
		test_cases.push_back( test_case_static_string_append_113() );

		test_cases.push_back( test_case_static_string_operator_plus_11() );
		test_cases.push_back( test_case_static_string_operator_plus_12() );
		test_cases.push_back( test_case_static_string_operator_plus_13() );

		test_cases.push_back( test_case_static_string_operator_plus_21() );
		test_cases.push_back( test_case_static_string_operator_plus_22() );
		test_cases.push_back( test_case_static_string_operator_plus_23() );

		test_cases.push_back( test_case_static_string_operator_plus_31() );
		test_cases.push_back( test_case_static_string_operator_plus_32() );
		test_cases.push_back( test_case_static_string_operator_plus_33() );

		test_cases.push_back( test_case_static_string_operator_plus_41() );
		test_cases.push_back( test_case_static_string_operator_plus_42() );
		test_cases.push_back( test_case_static_string_operator_plus_43() );

		test_cases.push_back( test_case_static_string_operator_plus_51() );
		test_cases.push_back( test_case_static_string_operator_plus_52() );
		test_cases.push_back( test_case_static_string_operator_plus_53() );

		test_cases.push_back( test_case_static_string_operator_plus_61() );
		test_cases.push_back( test_case_static_string_operator_plus_62() );
		test_cases.push_back( test_case_static_string_operator_plus_63() );

		test_cases.push_back( test_case_static_string_replace_11() );
		test_cases.push_back( test_case_static_string_replace_12() );
		test_cases.push_back( test_case_static_string_replace_13() );

		test_cases.push_back( test_case_static_string_replace_21() );
		test_cases.push_back( test_case_static_string_replace_22() );
		test_cases.push_back( test_case_static_string_replace_23() );

		test_cases.push_back( test_case_static_string_replace_31() );
		test_cases.push_back( test_case_static_string_replace_32() );
		test_cases.push_back( test_case_static_string_replace_33() );

		test_cases.push_back( test_case_static_string_replace_41() );
		test_cases.push_back( test_case_static_string_replace_42() );
		test_cases.push_back( test_case_static_string_replace_43() );

		test_cases.push_back( test_case_static_string_replace_51() );
		test_cases.push_back( test_case_static_string_replace_52() );
		test_cases.push_back( test_case_static_string_replace_53() );

		test_cases.push_back( test_case_static_string_replace_61() );
		test_cases.push_back( test_case_static_string_replace_62() );
		test_cases.push_back( test_case_static_string_replace_63() );
		test_cases.push_back( test_case_static_string_replace_64() );
		test_cases.push_back( test_case_static_string_replace_65() );
		test_cases.push_back( test_case_static_string_replace_66() );

		test_cases.push_back( test_case_static_string_replace_71() );
		test_cases.push_back( test_case_static_string_replace_72() );
		test_cases.push_back( test_case_static_string_replace_73() );
		test_cases.push_back( test_case_static_string_replace_74() );
		test_cases.push_back( test_case_static_string_replace_75() );
		test_cases.push_back( test_case_static_string_replace_76() );

		test_cases.push_back( test_case_static_string_replace_81() );
		test_cases.push_back( test_case_static_string_replace_82() );
		test_cases.push_back( test_case_static_string_replace_83() );
		test_cases.push_back( test_case_static_string_replace_84() );
		test_cases.push_back( test_case_static_string_replace_85() );
		test_cases.push_back( test_case_static_string_replace_86() );

		test_cases.push_back( test_case_static_string_replace_91() );
		test_cases.push_back( test_case_static_string_replace_92() );
		test_cases.push_back( test_case_static_string_replace_93() );

		test_cases.push_back( test_case_static_string_replace_101() );
		test_cases.push_back( test_case_static_string_replace_102() );
		test_cases.push_back( test_case_static_string_replace_103() );

		test_cases.push_back( test_case_static_string_replace_111() );
		test_cases.push_back( test_case_static_string_replace_112() );
		test_cases.push_back( test_case_static_string_replace_113() );

		test_cases.push_back( test_case_static_string_replace_121() );
		test_cases.push_back( test_case_static_string_replace_122() );
		test_cases.push_back( test_case_static_string_replace_123() );

		test_cases.push_back( test_case_static_string_replace_131() );
		test_cases.push_back( test_case_static_string_replace_132() );
		test_cases.push_back( test_case_static_string_replace_133() );

		test_cases.push_back( test_case_static_string_replace_141() );
		test_cases.push_back( test_case_static_string_replace_142() );
		test_cases.push_back( test_case_static_string_replace_143() );

		test_cases.push_back( test_case_static_string_replace_151() );
		test_cases.push_back( test_case_static_string_replace_152() );
		test_cases.push_back( test_case_static_string_replace_153() );

		test_cases.push_back( test_case_static_string_copy_1() );
		test_cases.push_back( test_case_static_string_copy_2() );
		test_cases.push_back( test_case_static_string_copy_3() );

		test_cases.push_back( test_case_static_string_swap_1() );

		{
			auto tests = test_case_static_string_find_1();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_find_2();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_find_3();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_find_4();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_find_5();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_find_6();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}


		{
			auto tests = test_case_static_string_rfind_1();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_rfind_2();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_rfind_3();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_rfind_4();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_rfind_5();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_rfind_6();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_1();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_2();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_3();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_4();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_5();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_6();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_7();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_8();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_compare_9();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_starts_with_1();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_starts_with_2();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_starts_with_3();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_ends_with_1();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_ends_with_2();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		{
			auto tests = test_case_static_string_ends_with_3();
			test_cases.insert( test_cases.end(), tests.begin(), tests.end() );
		}

		test_cases.push_back( test_case_static_string_operator_1() );
		test_cases.push_back( test_case_static_string_operator_2() );
		test_cases.push_back( test_case_static_string_operator_3() );
		test_cases.push_back( test_case_static_string_operator_4() );
		test_cases.push_back( test_case_static_string_operator_5() );

		test_cases.push_back( test_case_static_string_operator_6() );
		test_cases.push_back( test_case_static_string_operator_7() );
		test_cases.push_back( test_case_static_string_operator_8() );

		test_cases.push_back( test_case_static_string_ostream_1() );

		test_cases.push_back( test_case_static_string_constructor_1() );
		test_cases.push_back( test_case_static_string_constructor_2() );

		test_cases.push_back( test_case_static_string_capacity_1() );

		test_cases.push_back( test_case_static_string_max_size_1() );

		test_cases.push_back( test_case_static_string_reserve_1() );
		test_cases.push_back( test_case_static_string_reserve_2() );

		test_cases.push_back( test_case_static_string_resize_1() );
		test_cases.push_back( test_case_static_string_resize_2() );
		test_cases.push_back( test_case_static_string_resize_3() );

		test_cases.push_back( test_case_static_string_c_str_1() );

		test_cases.push_back( test_case_static_string_operator_assign_1() );
		test_cases.push_back( test_case_static_string_operator_assign_2() );
		test_cases.push_back( test_case_static_string_operator_assign_3() );
		test_cases.push_back( test_case_static_string_operator_assign_4() );
		test_cases.push_back( test_case_static_string_operator_assign_5() );
		test_cases.push_back( test_case_static_string_operator_assign_6() );
		test_cases.push_back( test_case_static_string_operator_assign_7() );
		test_cases.push_back( test_case_static_string_operator_assign_8() );

		test_cases.push_back( test_case_static_string_operator_to_basic_string_1() );

		test_cases.push_back( test_case_static_string_assign_1() );
		test_cases.push_back( test_case_static_string_assign_2() );
		test_cases.push_back( test_case_static_string_assign_3() );
		test_cases.push_back( test_case_static_string_assign_4() );
		test_cases.push_back( test_case_static_string_assign_5() );

		test_cases.push_back( test_case_static_string_assign_6() );
		test_cases.push_back( test_case_static_string_assign_7() );

		test_cases.push_back( test_case_static_string_assign_8() );
		test_cases.push_back( test_case_static_string_assign_9() );

		test_cases.push_back( test_case_static_string_assign_10() );

		test_cases.push_back( test_case_static_string_assign_11() );
		test_cases.push_back( test_case_static_string_assign_12() );
		test_cases.push_back( test_case_static_string_assign_13() );
		test_cases.push_back( test_case_static_string_assign_14() );
		test_cases.push_back( test_case_static_string_assign_15() );

#if __cpp_lib_string_contains >= 202011L
		test_cases.push_back( test_case_static_string_contains_1() );
		test_cases.push_back( test_case_static_string_contains_2() );
		test_cases.push_back( test_case_static_string_contains_3() );
		test_cases.push_back( test_case_static_string_contains_4() );
		test_cases.push_back( test_case_static_string_contains_5() );
		test_cases.push_back( test_case_static_string_contains_6() );
#else
		test_cases.push_back( test_case_static_string_contains_7() );
		test_cases.push_back( test_case_static_string_contains_8() );
		test_cases.push_back( test_case_static_string_contains_9() );
		test_cases.push_back( test_case_static_string_contains_10() );
		test_cases.push_back( test_case_static_string_contains_11() );
		test_cases.push_back( test_case_static_string_contains_12() );
#endif

		test_cases.push_back( test_case_static_string_substr_1() );
		test_cases.push_back( test_case_static_string_substr_2() );
*/

		test_cases.push_back( test_case_init_span_vector1() );
		test_cases.push_back( test_case_init_span_vector2() );
		test_cases.push_back( test_case_init_span_vector3() );

		test_cases.push_back( test_case_span_vector_operator_assign1() );
		test_cases.push_back( test_case_span_vector_operator_assign2() );
		test_cases.push_back( test_case_span_vector_operator_assign3() );

		test_cases.push_back( test_case_span_vector_assign1() );
		test_cases.push_back( test_case_span_vector_assign2() );
		test_cases.push_back( test_case_span_vector_assign3() );

		test_cases.push_back( test_case_span_vector_size1() );

		test_cases.push_back( test_case_span_vector_capacity1() );

		test_cases.push_back( test_case_span_vector_reserve1() );
		test_cases.push_back( test_case_span_vector_reserve2() );

		test_cases.push_back( test_case_span_vector_at1() );
		test_cases.push_back( test_case_span_vector_at2() );
		test_cases.push_back( test_case_span_vector_at3() );

		test_cases.push_back( test_case_span_vector_operator_at1() );
		test_cases.push_back( test_case_span_vector_operator_at2() );

		test_cases.push_back( test_case_span_vector_front1() );
		test_cases.push_back( test_case_span_vector_front2() );
		test_cases.push_back( test_case_span_vector_front3() );

		test_cases.push_back( test_case_span_vector_back1() );
		test_cases.push_back( test_case_span_vector_back2() );
		test_cases.push_back( test_case_span_vector_back3() );

		test_cases.push_back( test_case_span_vector_begin1() );
		test_cases.push_back( test_case_span_vector_begin2() );

		test_cases.push_back( test_case_span_vector_clear1() );

		test_cases.push_back( test_case_span_vector_insert1() );
		test_cases.push_back( test_case_span_vector_insert2() );

		ColBuilder col;

		const int COL_IDX 		= col.addCol( "Idx" );
		const int COL_NAME 		= col.addCol( "Test" );
		const int COL_RESULT    = col.addCol( "Result" );
		const int COL_EXPTECTED = col.addCol( "Expected" );
		const int COL_TEST_RES	= col.addCol( "Test Result" );

		unsigned idx = 0;

		for( auto & test : test_cases ) {

			idx++;

			CPPDEBUG( Tools::format( "run test: %s", test->getName() ) );

			col.addColData( COL_IDX, format( "% 2d", idx ) );
			col.addColData( COL_NAME, test->getName() );

			std::string result;
			std::string expected_result = "true";

			if( !test->getExpectedResult() ) {
				expected_result = "false";
			}

			std::string test_result;

#if __cpp_exceptions > 0
			try {
#endif

				if( test->throwsException() ) {
					 expected_result = "exception";
				}

				if( test->run() ) {
					result = "true";
				} else {
					result = "false";
				}

#if __cpp_exceptions > 0
			} catch( const std::exception & error ) {
				result = "exception";
				CPPDEBUG( format( "Error: %s", error.what() ));
			} catch( ... ) {
				result = "exception";
				CPPDEBUG( "Error" );
			}
#endif

			if( result != expected_result ) {
				test_result = co.color_output( ColoredOutput::RED, "failed" );
			} else {
				test_result = co.color_output( ColoredOutput::GREEN, "succeeded" );
			}

			col.addColData( COL_RESULT, result );
			col.addColData( COL_EXPTECTED, expected_result );
			col.addColData( COL_TEST_RES, test_result );

		}

		std::cout << col.toString() << std::endl;

#if __cpp_exceptions > 0
	} catch( const std::exception & error ) {
		std::cout << "Error: " << error.what() << std::endl;
		return 1;
	}
#endif

	return 0;
}

