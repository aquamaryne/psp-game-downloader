import { Module } from '@nestjs/common';
import { PspController } from './psp.controller';

@Module({
  controllers: [PspController]
})
export class PspModule {}
