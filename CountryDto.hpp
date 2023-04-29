#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class CountryDto : public oatpp::DTO {

	DTO_INIT(CountryDto, DTO)

		DTO_FIELD(String, name);
	DTO_FIELD(String, capital);
	DTO_FIELD(Int32, population);
	DTO_FIELD(Int32, gdp);
	DTO_FIELD(String, leader);
	DTO_FIELD(String, currency);

};
#include OATPP_CODEGEN_END(DTO)