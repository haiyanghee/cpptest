#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class SQLQueryHelper
{
    public:
	typedef std::pair<std::string, std::string>
	    SQLKeyVal; // pair of string     ■ Use 'using' instead of 'typedef'
		       // (fix available)
	typedef const std::vector<SQLKeyVal>
	    &SQLConstraints; // vector of pairs of constraints     ■■ Use
			     // 'using' instead of 'typedef' (fix available)
	typedef const std::vector<std::string>
	    &SQLRows; // vector of pairs of constraints     ■■ Use 'using'
		      // instead of 'typedef' (fix available)

	// given a table name and query constraints, check if the query result
	// is empty this doesn't return you the query results! Only tells you if
	// the result is empty or not
	static bool isResultEmpty(const std::string &tableName,
				  SQLQueryHelper::SQLConstraints constraints);
	static std::string
	createSQLQuery(const std::string &tableName,
		       SQLQueryHelper::SQLRows rows,
		       SQLQueryHelper::SQLConstraints constraints);

	static std::string wrapQuotesAround(const std::string &str);

}; // class SQLQueryHelper


bool SQLQueryHelper::isResultEmpty(const std::string &tableName,
				   SQLQueryHelper::SQLConstraints constraints)
{
	std::string lSql = createSQLQuery(tableName, {}, constraints);
	std::cout << "sql string is: '" << lSql << "'\n";
	return false;
}


std::string
SQLQueryHelper::createSQLQuery(const std::string &tableName,
			       SQLQueryHelper::SQLRows rows,
			       SQLQueryHelper::SQLConstraints constraints)
{
	std::stringstream ss;
	ss << "select ";
	// if want to select non-empty number of rows
	if (rows.size() > 0) {
		// add in the first row
		ss << rows[0];
		// add the rest
		for (size_t i = 1; i < rows.size(); ++i) {
			ss << ", " << rows[i];
		}
	} else {
		ss << " * ";
	}
	ss << " from " << tableName;

	// if have constraints
	if (constraints.size() > 0) {
		ss << " where ";
		// add in the first pair
		ss << constraints[0].first << " = " << constraints[0].second;
		// add the rest
		for (size_t i = 1; i < constraints.size(); ++i) {
			ss << " and " << constraints[i].first << " = "
			   << constraints[i].second;
		}
	}
	// end query
	ss << ";";
	return ss.str();
}

std::string SQLQueryHelper::wrapQuotesAround(const std::string &str)
{
	return "'" + str + "'";
}

int main()
{
	SQLQueryHelper::isResultEmpty("GENCCC", {});
	SQLQueryHelper::isResultEmpty(
	    "GENCCC", {{"COID", SQLQueryHelper::wrapQuotesAround("asdf")}});

	SQLQueryHelper::isResultEmpty(
	    "GENCCC", {{"COID", SQLQueryHelper::wrapQuotesAround("asdf")},
		       {"Col2", SQLQueryHelper::wrapQuotesAround("hii")},
		       {"Col3", "3"}});
}
