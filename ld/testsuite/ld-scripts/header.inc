      /* HEADER */
      FILL(0xFF)
      QUAD(0xEFBEADDE45444F43);
      crc64 = .;
      QUAD(0)
      ecc_start = .;
      /* Program Entry */
      LONG(entry)

      /* Program size */
      LONG(ecc_end - ecc_start)

      /* Time Stamp */
      time_since_epoch = .;
      QUAD(0)

      /* 32 bytes here */
      /* Version info */
      BYTE(1)
      BYTE(2)
      BYTE(3)
      BYTE(4)
      LONG(0x17)
      LONG(0x11470000)
      LONG(0xEFBEADDE)
      /* 48 bytes here */
      ASCII (16) "program name"
      /* 64 bytes here */
      ASCII (64) "empty"
      ASCII (32) "comment 1\n"
      ASCII (32) "comment 2\n"
      ASCII (32) "comment 3\n"
      ASCII (24) "comment 4\n"
      QUAD(0x45444F43EFBEADDE);
