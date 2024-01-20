import { Component, Input, OnInit } from '@angular/core';
import { INoticia } from 'src/app/data/data';
import { NewsService } from 'src/app/news.service';

@Component({
  selector: 'app-small-card',
  templateUrl: './small-card.component.html',
  styleUrls: ['./small-card.component.css']
})
export class SmallCardComponent implements OnInit {

  @Input()
  photoCover:string = ""
  @Input()
  cardTitle:string = ""
  @Input()
  Id:string="0"

  noticias: INoticia[] | any

  constructor(private newsService: NewsService) { }

  ngOnInit(): void {

    this.noticias = this.newsService.getAll()
    // this.newsService.getAllNews().subscribe(data => {
    //   // Excluindo o item com ID 1 da lista
    //   this.smallCardList = data.filter(item => item.id !== '1');
    // });
  }

}
