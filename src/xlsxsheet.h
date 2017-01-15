#ifndef XLSXSHEET_
#define XLSXSHEET_

#include <Rcpp.h>
#include "rapidxml.h"
#include "xlsxbook.h"

class xlsxsheet {

  public:

    std::string name_;

    double defaultRowHeight_;
    double defaultColWidth_;
    std::vector<double> colWidths_;
    xlsxbook& book_; // reference to parent workbook
    Rcpp::DataFrame information_; // Wrapper for variables returned to R

    // The remaining variables go to R
    Rcpp::CharacterVector address_;   // Value of cell node r
    Rcpp::IntegerVector   row_;       // Parsed address_ (one-based)
    Rcpp::IntegerVector   col_;       // Parsed address_ (one-based)
    Rcpp::CharacterVector content_;   // Unparsed value of cell node v
    Rcpp::CharacterVector formula_;   // If present
    Rcpp::CharacterVector formula_type_; // If present
    Rcpp::CharacterVector formula_ref_;  // If present
    Rcpp::IntegerVector   formula_group_; // If present

    Rcpp::List  value_;               // Parsed values wrapped in unnamed lists
    Rcpp::CharacterVector type_;      // value of cell node t
    Rcpp::CharacterVector data_type_; // Type of the parsed value

    Rcpp::CharacterVector error_;     // Parsed value
    Rcpp::LogicalVector   logical_;   // Parsed value
    Rcpp::NumericVector   numeric_;   // Parsed value
    Rcpp::NumericVector   date_;      // Parsed value
    Rcpp::CharacterVector character_; // Parsed value

    // The following are always used.
    Rcpp::NumericVector   height_;          // Provided to cell constructor
    Rcpp::NumericVector   width_;           // Provided to cell constructor
    Rcpp::IntegerVector   style_format_id_; // cellXfs xfId links to cellStyleXfs entry
    Rcpp::IntegerVector   local_format_id_; // cell 'c' links to cellXfs entry

    xlsxsheet(const int& sheetindex, xlsxbook& book);
    Rcpp::DataFrame& information();       // Cells contents and styles DF wrapped in list

    void cacheDefaultRowColDims(rapidxml::xml_node<>* worksheet);
    void cacheColWidths(rapidxml::xml_node<>* worksheet);
    unsigned long long int cacheCellcount(rapidxml::xml_node<>* sheetData);
    void initializeColumns(rapidxml::xml_node<>* sheetData);
    void parseSheetData(rapidxml::xml_node<>* sheetData);

};

#endif
