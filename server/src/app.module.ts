import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { PspService } from './modules/psp/psp.service';
import { PspModule } from './modules/psp/psp.module';

@Module({
  imports: [PspModule],
  controllers: [AppController],
  providers: [AppService, PspService],
})
export class AppModule {}
