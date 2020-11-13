require 'minitest/autorun'
require 'ldl'



class TestPullResp < Minitest::Test

    include LDL

    def setup
        @state = Semtech::PullResp.new
    end

    def test_encode_default    
        
        out = @state.encode    
        
        iter = out.unpack("CS>Ca*").each
        
        assert_equal Semtech::Message::VERSION, iter.next
        iter.next
        
        assert_equal @state.class.type, iter.next
        
        JSON.parse iter.next
        
    end
    
    def test_decode_default
        
        input = @state.encode
        
        input = "\x02\x00\x00\x03#{{:txpk => Semtech::TXPacket.new}.to_json}"
        
        decoded = Semtech::PullResp.decode(input)
        
        assert_equal 0, decoded.token
        
    end
    
    def test_encode_decode        
        assert_kind_of Semtech::PullResp, Semtech::Message.decode(@state.encode)        
    end

    def test_decode_real
        input = "\x02\x46\x8E\x03\x7B\x22\x74\x78\x70\x6B\x22\x3A\x7B\x22\x69\x6D\x6D\x65\x22\x3A\x66\x61\x6C\x73\x65\x2C\x22\x74\x6D\x73\x74\x22\x3A\x35\x31\x31\x33\x34\x32\x30\x2C\x22\x66\x72\x65\x71\x22\x3A\x38\x36\x38\x2E\x31\x2C\x22\x72\x66\x63\x68\x22\x3A\x30\x2C\x22\x70\x6F\x77\x65\x22\x3A\x31\x34\x2C\x22\x6D\x6F\x64\x75\x22\x3A\x22\x4C\x4F\x52\x41\x22\x2C\x22\x64\x61\x74\x72\x22\x3A\x22\x53\x46\x37\x42\x57\x31\x32\x35\x22\x2C\x22\x63\x6F\x64\x72\x22\x3A\x22\x34\x2F\x35\x22\x2C\x22\x69\x70\x6F\x6C\x22\x3A\x74\x72\x75\x65\x2C\x22\x73\x69\x7A\x65\x22\x3A\x33\x33\x2C\x22\x6E\x63\x72\x63\x22\x3A\x74\x72\x75\x65\x2C\x22\x64\x61\x74\x61\x22\x3A\x22\x49\x47\x33\x59\x59\x45\x6D\x56\x54\x74\x78\x38\x42\x75\x79\x52\x43\x6D\x79\x36\x6D\x72\x68\x35\x42\x4C\x32\x4E\x6A\x49\x55\x4B\x6F\x6A\x6F\x72\x6B\x39\x43\x4C\x30\x58\x51\x67\x22\x7D\x7D"
        Semtech::PullResp.decode(input)
    end

end