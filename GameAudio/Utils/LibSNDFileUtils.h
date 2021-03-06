/**
  * @file   LibSNDFileUtils.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  LibSNDFileUtils is a utility class providing
  * adhoc functions that help us deal with the libSNDFile library
*/

#ifndef LIBSNDFILEUTILS_H
#define LIBSNDFILEUTILS_H

// libSndFile Includes
#include <sndfile.hh>

/** Utils is a name space
    for our AudioWrapper
    Utilities **/
namespace Utils
{
    //! Convert an AL Error Enumeration into a readable String
    inline extern std::string getSFErrorString(int errorCode)
    {
        switch(errorCode)
        {
            case SF_ERR_NO_ERROR:
            {
                return "SF_ERR_NO_ERROR";
                break;
            }
            case SF_ERR_UNRECOGNISED_FORMAT:
            {
                return "SF_ERR_UNRECOGNISED_FORMAT";
                break;
            }
            case SF_ERR_SYSTEM:
            {
                return "SF_ERR_SYSTEM";
                break;
            }
            case SF_ERR_MALFORMED_FILE:
            {
                return "SF_ERR_MALFORMED_FILE";
                break;
            }
            case SF_ERR_UNSUPPORTED_ENCODING:
            {
                return "SF_ERR_UNSUPPORTED_ENCODING";
                break;
            }
            default:
            {
                return "SF_UNKOWN_ERROR";
                break;
            }
        }
    }
}


#endif // LIBSNDFILEUTILS_H
