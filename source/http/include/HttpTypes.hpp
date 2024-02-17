#pragma once

namespace utils
{
    enum HttpVersion
    {
        HVersion_None = 0,
        HVersion_Http10,
        HVersion_Http11,
        HVersion_Http20
    };

    enum HttpStatusCode
    {
        HStat_Unknown                       = 0,

        // Information responses
        HStat_Continue                      = 100,
        HStat_SwitchingProtocols            = 101,
        HStat_Processing                    = 102,
        HStat_EarlyHints                    = 103,

        // Successful responses
        HStat_OK                            = 200,
        HStat_Created                       = 201,
        HStat_Accepted                      = 202,
        HStat_NonAuthoritativeInfo          = 203,
        HStat_NoContent                     = 204,
        HStat_ResetContent                  = 205,
        HStat_PartialContent                = 206,
        HStat_MultiStatus                   = 207,
        HStat_AlreadyReported               = 208,
        HStat_IMUsed                        = 226,

        // Redirection messages
        HStat_MultipleChoices               = 300,
        HStat_MovedPermanently              = 301,
        HStat_Found                         = 302,
        HStat_SeeOther                      = 303,
        HStat_NotModified                   = 304,
        HStat_UseProxy                      = 305,
        HStat_Unused                        = 306,
        HStat_TemporaryRedirect             = 307,
        HStat_PermanentRedicrect            = 308,

        // Client error messages
        HStat_BadRequest                    = 400,
        HStat_Unauthorized                  = 401,
        HStat_PaymentRequired               = 402,
        HStat_Forbidden                     = 403,
        HStat_NotFound                      = 404,
        HStat_MethodNotAllowed              = 405,
        HStat_NotAcceptable                 = 406,
        HStat_ProxyAuthRequired             = 407,
        HStat_RequestTimeout                = 408,
        HStat_Conflict                      = 409,
        HStat_Gone                          = 410,
        HStat_LengthRequired                = 411,
        HStat_PreconditionedFailed          = 412,
        HStat_PayloadTooLarge               = 413,
        HStat_URITooLong                    = 414,
        HStat_UnsupportedMediaType          = 415,
        HStat_RangeNotSatisfiable           = 416,
        HStat_ExpectationFailed             = 417,
        HStat_ImATeapot                     = 418,
        HStat_MisdirectedRequest            = 421,
        HStat_UnprocessableContent          = 422,
        HStat_Locked                        = 423,
        HStat_FailedDependency              = 424,
        HStat_TooEarly                      = 425,
        HStat_UpgradeRequired               = 426,
        HStat_PreconditionRequired          = 428,
        HStat_TooManyRequests               = 429,
        HStat_RequestHeaderFieldsTooLarge   = 431,
        HStat_UnavailableForLegalReasons    = 451,

        // Server error responses
        HStat_InternalServerError           = 500,
        HStat_NotImplemented                = 501,
        HStat_BadGateway                    = 502,
        HStat_ServiceUnavailable            = 503,
        HStat_GatewayTimeout                = 504,
        HStat_HTTPVersionNotSupported       = 505,
        HStat_VariantAlsoNegotiates         = 506,
        HStat_InsufficientStorage           = 507,
        HStat_LoopDetected                  = 508,
        HStat_NotExtended                   = 510,
        HStat_NetworkAuthRequired           = 511
    };

    // TODO : Finish this some other time. Seems like a lot of time to investigate
    // List of common content types:
    // https://stackoverflow.com/questions/23714383/what-are-all-the-possible-values-for-http-content-type-header
    enum ContentType
    {
        CT_None = 0,
        CT_Text_HTML,
        CT_Text_CSS,
        CT_Text_Javascript
    };
}