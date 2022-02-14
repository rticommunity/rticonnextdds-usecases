

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from cc_str_com_types.idl
using RTI Code Generator (rtiddsgen) version 3.1.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef cc_str_com_types_357124301_hpp
#define cc_str_com_types_357124301_hpp

#include <iosfwd>

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/Optional.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/core/array.hpp"
#include "rti/core/BoundedSequence.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#include "rti/core/LongDouble.hpp"
#include "dds/core/External.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/topic/TopicTraits.hpp"

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace cctypes {

    static const uint32_t MAX_SEQUENCE_LEN = 18800000UL;

    static const uint8_t KEY_STRING_LEN = 8;

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    // On Windows, dll-export template instantiations of standard types used by
    // other dll-exported types
    template class NDDSUSERDllExport std::allocator< uint8_t >;
    template class NDDSUSERDllExport std::vector< uint8_t >;
    #endif
    class NDDSUSERDllExport ccBulk {
      public:
        ccBulk();

        ccBulk(
            const std::string& pub_id,
            const ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >& data);

        #ifdef RTI_CXX11_RVALUE_REFERENCES
        #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
        ccBulk (ccBulk&&) = default;
        ccBulk& operator=(ccBulk&&) = default;
        ccBulk& operator=(const ccBulk&) = default;
        ccBulk(const ccBulk&) = default;
        #else
        ccBulk(ccBulk&& other_) OMG_NOEXCEPT;  
        ccBulk& operator=(ccBulk&&  other_) OMG_NOEXCEPT;
        #endif
        #endif 

        std::string& pub_id() OMG_NOEXCEPT {
            return m_pub_id_;
        }

        const std::string& pub_id() const OMG_NOEXCEPT {
            return m_pub_id_;
        }

        void pub_id(const std::string& value) {
            m_pub_id_ = value;
        }

        void pub_id(std::string&& value) {
            m_pub_id_ = std::move(value);
        }
        ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >& data() OMG_NOEXCEPT {
            return m_data_;
        }

        const ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >& data() const OMG_NOEXCEPT {
            return m_data_;
        }

        void data(const ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >& value) {
            m_data_ = value;
        }

        void data(::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >&& value) {
            m_data_ = std::move(value);
        }

        bool operator == (const ccBulk& other_) const;
        bool operator != (const ccBulk& other_) const;

        void swap(ccBulk& other_) OMG_NOEXCEPT ;

      private:

        std::string m_pub_id_;
        ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) > m_data_;

    };

    inline void swap(ccBulk& a, ccBulk& b)  OMG_NOEXCEPT 
    {
        a.swap(b);
    }

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ccBulk& sample);

} // namespace cctypes  

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< cctypes::ccBulk > {
            NDDSUSERDllExport static std::string value() {
                return "cctypes::ccBulk";
            }
        };

        template<>
        struct is_topic_type< cctypes::ccBulk > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< cctypes::ccBulk > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const cctypes::ccBulk& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(cctypes::ccBulk& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(cctypes::ccBulk& sample);

            NDDSUSERDllExport 
            static void allocate_sample(cctypes::ccBulk& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };

    }
}

namespace rti { 
    namespace topic {

        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct dynamic_type< cctypes::ccBulk > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };
        #endif

        template <>
        struct extensibility< cctypes::ccBulk > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;                
        };

    }
}

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // cc_str_com_types_357124301_hpp

