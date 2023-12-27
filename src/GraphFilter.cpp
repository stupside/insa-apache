#include "header/GraphFilter.h"

#include <iostream>

const std::string GraphFilter::DOMAIN_DISABLED = "";

const unsigned int GraphFilter::HOUR_SPAN = 1;
const unsigned int GraphFilter::HOUR_DISABLED = 25;

GraphFilter::GraphFilter()
{
#ifdef MAP
    std::cout << "MAP: Creating a new graph filter" << std::endl;
#endif
    _span = HOUR_SPAN;
    _hour = HOUR_DISABLED;

    _domain = DOMAIN_DISABLED;
    _extensions = std::set<std::string>();
}

bool GraphFilter::ShouldIgnoreHour(unsigned int hour) const
{
    if (_hour == HOUR_DISABLED)
    {
#ifdef DEBUG
        std::cout << "DEBUG: No hour filter applied" << std::endl;
#endif
        return false;
    }

    bool ignore = hour + 1 < _hour || hour + 1 > _hour + _span;

#ifdef DEBUG
    if (ignore)
    {
        std::cout << "DEBUG: Ignoring hour " << hour + 1 << " (filter: " << _hour << "h - " << _hour + _span << "h)" << std::endl;
    }
#endif

    return ignore;
}

bool GraphFilter::ShouldIgnoreDomain(const std::string &domain) const
{
    if (_domain == DOMAIN_DISABLED)
    {
#ifdef DEBUG
        std::cout << "DEBUG: No domain filter applied" << std::endl;
#endif
        return false;
    }

    bool ignore = domain != _domain;

#ifdef DEBUG
    if (ignore)
    {
        std::cout << "DEBUG: Ignoring domain " << domain << " (filter: " << _domain << ")" << std::endl;
    }
#endif

    return ignore;
}

bool GraphFilter::ShouldIgnoreExtension(const std::string &path) const
{
    if (_extensions.empty())
    {
#ifdef DEBUG
        std::cout << "DEBUG: No extension filter applied" << std::endl;
#endif
        return false;
    }

    const std::string extension = path.substr(path.find_last_of('.') + 1);

    bool ignore = _extensions.find(extension) != _extensions.end();

#ifdef DEBUG
    if (ignore)
    {
        std::cout << "DEBUG: Ignoring extension " << extension << " (filter: ";

        for (const auto &extension : _extensions)
        {
            std::cout << extension << ",";
        }

        std::cout << ")" << std::endl;
    }
#endif

    return ignore;
}

GraphFilter &GraphFilter::FilterByHour(unsigned int hour, unsigned int span)
{
    _hour = hour;
    _span = span;

    return *this;
}

GraphFilter &GraphFilter::FilterByDomain(const std::string &domain)
{
    _domain = std::move(domain);

    return *this;
}

GraphFilter &GraphFilter::FilterByExtension(const std::string &extension)
{
    _extensions.insert(extension);

    return *this;
}
std::ostream &operator<<(std::ostream &os, const GraphFilter &filter)
{
    if (filter._hour == GraphFilter::HOUR_DISABLED && filter._domain == GraphFilter::DOMAIN_DISABLED && filter._extensions.empty())
    {
        return os;
    }

    os << "Warning: the following filters are applied:" << std::endl;

    if (filter._hour != GraphFilter::HOUR_DISABLED)
    {
        os << " - logs between " << filter._hour << "h and " << filter._hour + filter._span << "h" << std::endl;
    }

    if (filter._domain != GraphFilter::DOMAIN_DISABLED)
    {
        os << " - logs from the domain " << filter._domain << std::endl;
    }

    if (!filter._extensions.empty())
    {
        os << " - logs with the following extensions: ";

        for (const auto &extension : filter._extensions)
        {
            os << extension << ",";
        }

        os << std::endl;
    }

    return os;
}

GraphFilter::~GraphFilter()
{
#ifdef MAP
    std::cout << "MAP: Deleting a graph filter" << std::endl;
#endif
}