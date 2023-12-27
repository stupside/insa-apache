#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <set>
#include <string>

/**
 * An object that represents a filter used to filter nodes during the graph creation from a log file.
 */
class GraphFilter
{
private:
    /**
     * The logs should be filtered by hour.
     */
    unsigned int _hour;

    /**
     * The logs should be filtered by hour. From _hour to _hour + _span.
     */
    unsigned int _span;

    /**
     * The logs should be filtered by domain.
     */
    std::string _domain;

    /**
     * The logs should be filtered by extension.
     */
    std::set<std::string> _extensions;

public:
    /**
     * Default hour span.
     */
    static const unsigned int HOUR_SPAN;

    /**
     * A constant to disable the hour filter.
     */
    static const unsigned int HOUR_DISABLED;

    /**
     * A constant to disable the domain filter.
     */
    static const std::string DOMAIN_DISABLED;

    /**
     * Default constructor.
     */
    GraphFilter();

    /**
     * Filter the logs by extension.
     *
     * @param extension The extension to filter.
     * @return A reference to this object.
     */
    GraphFilter &FilterByExtension(const std::string &extension);

    /**
     * Filter the logs by domain.
     *
     * @param domain The domain to filter.
     * @return A reference to this object.
     */
    GraphFilter &FilterByDomain(const std::string &domain = DOMAIN_DISABLED);

    /**
     * Filter the logs by hour.
     *
     * @param hour The hour to filter.
     * @param span The span of hours to filter.
     * @return A reference to this object.
     */
    GraphFilter &FilterByHour(unsigned int hour = HOUR_DISABLED, unsigned int span = HOUR_SPAN);

    /**
     * Check if the hour is filtered.
     *
     * @param hour The hour to check.
     * @return True if the hour is filtered, false otherwise.
     */
    bool ShouldIgnoreHour(unsigned int hour) const;

    /**
     * Check if the domain is filtered.
     *
     * @param domain The domain to check.
     * @return True if the domain is filtered, false otherwise.
     */
    bool ShouldIgnoreDomain(const std::string &domain) const;

    /**
     * Check if the extension is filtered.
     *
     * @param path The path to check.
     * @return True if the extension is filtered, false otherwise.
     */
    bool ShouldIgnoreExtension(const std::string &path) const;

    ~GraphFilter();

    /**
     * Print the filter. A warning is shown if the filter is not empty.
     *
     * @param os The output stream.
     * @param filter The filter to print.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const GraphFilter &filter);
};

#endif // GRAPH_FILTER_H