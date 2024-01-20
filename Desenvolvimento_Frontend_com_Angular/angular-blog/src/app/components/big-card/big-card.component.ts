import { Component, Input, OnInit } from '@angular/core';
import { INoticia } from 'src/app/data/data';
import { NewsService } from 'src/app/news.service';

@Component({
  selector: 'app-big-card',
  templateUrl: './big-card.component.html',
  styleUrls: ['./big-card.component.css']
})
export class BigCardComponent implements OnInit {

  @Input()
  photoCover:string =""
  @Input()
  cardTitle:string= ""
  @Input()
  cardDescription:string =""
  @Input()
  Id:number= 0

  noticia: INoticia | any

  constructor(private newsService: NewsService) { }

  ngOnInit(): void {
    this.noticia  = this.newsService.getOne(1)
    this.photoCover = this.noticia.photoCover;
    this.cardTitle = this.noticia.title;
    this.cardDescription = this.noticia.description;
    this.Id = this.noticia.id;

    // this.newsService.getOne(1).subscribe(data => {
    //   this.photoCover = data.photoCover;
    //   this.cardTitle = data.title;
    //   this.cardDescription = data.description;
    //   this.Id = data.id;

    // });
  }


}
