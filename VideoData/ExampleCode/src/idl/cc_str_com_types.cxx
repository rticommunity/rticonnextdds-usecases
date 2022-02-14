

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from cc_str_com_types.idl
using RTI Code Generator (rtiddsgen) version 3.1.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>

#include "rti/topic/cdr/Serialization.hpp"

#include "cc_str_com_types.hpp"
#include "cc_str_com_typesPlugin.hpp"

#include <rti/util/ostream_operators.hpp>

namespace cctypes {

    // ---- ccBulk: 

    ccBulk::ccBulk() :
        m_pub_id_ ("")  {
    }   

    ccBulk::ccBulk (
        const std::string& pub_id,
        const ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) >& data)
        :
            m_pub_id_( pub_id ),
            m_data_( data ) {
    }

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    ccBulk::ccBulk(ccBulk&& other_) OMG_NOEXCEPT  :m_pub_id_ (std::move(other_.m_pub_id_))
    ,
    m_data_ (std::move(other_.m_data_))
    {
    } 

    ccBulk& ccBulk::operator=(ccBulk&&  other_) OMG_NOEXCEPT {
        ccBulk tmp(std::move(other_));
        swap(tmp); 
        return *this;
    }
    #endif
    #endif   

    void ccBulk::swap(ccBulk& other_)  OMG_NOEXCEPT 
    {
        using std::swap;
        swap(m_pub_id_, other_.m_pub_id_);
        swap(m_data_, other_.m_data_);
    }  

    bool ccBulk::operator == (const ccBulk& other_) const {
        if (m_pub_id_ != other_.m_pub_id_) {
            return false;
        }
        if (m_data_ != other_.m_data_) {
            return false;
        }
        return true;
    }
    bool ccBulk::operator != (const ccBulk& other_) const {
        return !this->operator ==(other_);
    }

    std::ostream& operator << (std::ostream& o,const ccBulk& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "pub_id: " << sample.pub_id()<<", ";
        o << "data: " << sample.data() ;
        o <<"]";
        return o;
    }

} // namespace cctypes  

// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        #ifndef NDDS_STANDALONE_TYPE
        template<>
        struct native_type_code< cctypes::ccBulk > {
            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode ccBulk_g_tc_pub_id_string;
                static DDS_TypeCode ccBulk_g_tc_data_sequence;

                static DDS_TypeCode_Member ccBulk_g_tc_members[2]=
                {

                    {
                        (char *)"pub_id",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"data",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ccBulk_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"cctypes::ccBulk", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        ccBulk_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ccBulk*/

                if (is_initialized) {
                    return &ccBulk_g_tc;
                }

                ccBulk_g_tc_pub_id_string = initialize_string_typecode(((cctypes::KEY_STRING_LEN)));
                ccBulk_g_tc_data_sequence = initialize_sequence_typecode< ::rti::core::bounded_sequence< uint8_t, (cctypes::MAX_SEQUENCE_LEN) > >(((cctypes::MAX_SEQUENCE_LEN)));

                ccBulk_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ccBulk_g_tc_data_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
                ccBulk_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ccBulk_g_tc_pub_id_string;
                ccBulk_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& ccBulk_g_tc_data_sequence;

                /* Initialize the values for member annotations. */
                ccBulk_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ccBulk_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

                ccBulk_g_tc._data._sampleAccessInfo = sample_access_info();
                ccBulk_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized = RTI_TRUE;

                return &ccBulk_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static RTIBool is_initialized = RTI_FALSE;

                cctypes::ccBulk *sample;

                static RTIXCdrMemberAccessInfo ccBulk_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ccBulk_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized) {
                    return (RTIXCdrSampleAccessInfo*) &ccBulk_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    cctypes::ccBulk);
                if (sample == NULL) {
                    return NULL;
                }

                ccBulk_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->pub_id() - (char *)sample);

                ccBulk_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->data() - (char *)sample);

                ccBulk_g_sampleAccessInfo.memberAccessInfos = 
                ccBulk_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(cctypes::ccBulk);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        ccBulk_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        ccBulk_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ccBulk_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ccBulk_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< cctypes::ccBulk >;

                ccBulk_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized = RTI_TRUE;
                return (RTIXCdrSampleAccessInfo*) &ccBulk_g_sampleAccessInfo;
            }

            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ccBulk_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ccBulk_g_typePlugin;
            }
        }; // native_type_code
        #endif

        const ::dds::core::xtypes::StructType& dynamic_type< cctypes::ccBulk >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< cctypes::ccBulk >::get())));
        }

    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< cctypes::ccBulk >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                cctypes::ccBulkPlugin_new,
                cctypes::ccBulkPlugin_delete);
        }

        std::vector<char>& topic_type_support< cctypes::ccBulk >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const cctypes::ccBulk& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ccBulkPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ccBulkPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< cctypes::ccBulk >::from_cdr_buffer(cctypes::ccBulk& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ccBulkPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create cctypes::ccBulk from cdr buffer");
        }

        void topic_type_support< cctypes::ccBulk >::reset_sample(cctypes::ccBulk& sample) 
        {
            sample.pub_id("");
            ::rti::topic::reset_sample(sample.data());
        }

        void topic_type_support< cctypes::ccBulk >::allocate_sample(cctypes::ccBulk& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.pub_id(),  -1, (cctypes::KEY_STRING_LEN));
            ::rti::topic::allocate_sample(sample.data(),  (cctypes::MAX_SEQUENCE_LEN), -1);
        }

    }
}  

