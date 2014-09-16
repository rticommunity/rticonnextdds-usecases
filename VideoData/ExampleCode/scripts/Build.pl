################################################################################
# (c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.
# RTI grants Licensee a license to use, modify, compile, and create derivative
# works of the Software.  Licensee has the right to distribute object form only
# for use with RTI products.  The Software is provided "as is", with no warranty
# of any type, including any warranty for fitness for any purpose. RTI is under
# no obligation to maintain or support the Software.  RTI shall not be liable 
# for any incidental or consequential damages arising out of the use or 
# inability to use the software.
################################################################################

#!C:/Perl64/bin/perl.exe -w

use Cwd;

# The first command prompt argument is the directory to check
$ARCHITECTURE = $ARGV[0];

if ($ARCHITECTURE eq "") {
   print "ERROR: You have to write an architecture to run this script, e.g.:\n";
   print "\tperl ./scripts/Build.pl i86Win32VS2010\n";
   exit(-1);
}

system "cmake -H./src -B./projects -DARCHITECTURE=" . $ARCHITECTURE;
if ( $? != 0 ) {
    print "ERROR trying to execute cmake\n";
    exit(1);
}
   
# $OS is the operating system 
$OS = $^O;

# if the operating system is windows, then we will use the msbuild compiler,
# else will use  make 
if ($OS =~ /[\s\S]*?Win[\s\S]*?/) {
    system "msbuild ./projects/StreamingVideo.sln";
    if ( $? != 0 ) {
        print "ERROR compiling ./projects/StreamingVideo.sln example\n";
        exit(1);
    }
    create_running_scripts("./scripts/VideoStreaming_windows.txt",
                "Publisher", $ARCHITECTURE);
    create_running_scripts("./scripts/VideoStreaming_windows.txt",
                "Subscriber", $ARCHITECTURE);
    print "\nCreated running scripts\n";
} elsif ($OS eq "linux") {
    chdir "./projects";
    system "make";
    if ( $? != 0 ) {
        print "ERROR compiling StreamingVideo example\n";
        exit(1);
    }
    chdir "..";
    create_running_scripts("./scripts/VideoStreaming_linux.txt",
                "Publisher", $ARCHITECTURE);
    create_running_scripts("./scripts/VideoStreaming_linux.txt",
                "Subscriber", $ARCHITECTURE);            
    print "\nCreated running scripts\n";
} elsif ($OS eq "darwin") {
    chdir "./projects";
    system "make";
    if ( $? != 0 ) {
        print "ERROR compiling StreamingVideo example\n";
        exit(1);
    }
    chdir "..";
    create_running_scripts("./scripts/VideoStreaming_linux.txt",
                "Publisher", $ARCHITECTURE);
    create_running_scripts("./scripts/VideoStreaming_linux.txt",
                "Subscriber", $ARCHITECTURE);            
    print "\nCreated running scripts\n";
}

sub create_running_scripts {
    my ($filename, $DDS_ENTITY,$arch) = @_;
    open(my $fh, '<:utf8', $filename)
        or die "Could not open file '$filename' $!";
        
    # To copy all the file in a string
    local $/ = undef;
    $buffer = <$fh>;
    $buffer =~ s/\$\{ARCHITECTURE\}/$arch/g;
    $buffer =~ s/\$\{DDS_ENTITY\}/$DDS_ENTITY/g;
    close $fh;

    if ($OS =~ /[\s\S]*?Win[\s\S]*?/) {   
        $new_file = "./scripts/Video".$DDS_ENTITY.".bat";
    } else {
        $new_file = "./scripts/Video".$DDS_ENTITY.".sh";
    }
    
    open(my $fh, '>:utf8', $new_file)
            or die "Could not create file <$new_file> $!";
    chmod 0775, $new_file;
    print $fh $buffer;
    close $fh;
}
